// Pinball game controller for an Arduino Mega 2560.
//
// - Slingshots and bumpers fire a solenoid when the ball hits their switch or contact ring.
// - Infrared sensors detect the ball in the top lanes and when it drains between the flippers;
//   a drained ball is sent back to the launch lane by a solenoid.
// - A target lights its LED and scores points.
// - The score and the remaining balls are shown on a 16x2 I2C LCD.
// - Above WHEEL_SCORE_THRESHOLD points, a NeoPixel wheel of fortune gives a random bonus once per game.
//
// Solenoids are driven through relay modules that are active LOW.

#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// ---------------------------------------------------------------------------
// Pins
// ---------------------------------------------------------------------------

// Solenoids (active LOW)
const uint8_t LAUNCH_SOLENOID_PIN = 48;  // sends a drained ball back to the launch lane
const uint8_t LEFT_SLINGSHOT_PIN = 42;
const uint8_t RIGHT_SLINGSHOT_PIN = 44;
const uint8_t LOWER_BUMPER_PIN = 46;
const uint8_t UPPER_LEFT_BUMPER_PIN = 52;
const uint8_t UPPER_RIGHT_BUMPER_PIN = 50;
const uint8_t SOLENOID_PINS[] = {LAUNCH_SOLENOID_PIN, LEFT_SLINGSHOT_PIN, RIGHT_SLINGSHOT_PIN,
                                 LOWER_BUMPER_PIN, UPPER_LEFT_BUMPER_PIN, UPPER_RIGHT_BUMPER_PIN};

// Slingshot microswitches (LOW when pressed)
const uint8_t LEFT_SLINGSHOT_SWITCH_PIN = A1;
const uint8_t RIGHT_SLINGSHOT_SWITCH_PIN = A0;

// Bumper contact rings (LOW when the ball touches the ring)
const uint8_t LOWER_BUMPER_RING_PIN = 26;
const uint8_t UPPER_LEFT_BUMPER_RING_PIN = 24;
const uint8_t UPPER_RIGHT_BUMPER_RING_PIN = 22;

// Targets (LOW when hit). Target 1 is wired but not used in this version of the game.
const uint8_t TARGET1_PIN = 31;
const uint8_t TARGET2_PIN = 37;
const uint8_t TARGET1_LED_PIN = 33;
const uint8_t TARGET2_LED_PIN = 35;

// Infrared sensors (LOW when the ball passes)
const uint8_t DRAIN_SENSOR_PIN = 2;  // between the two flippers: the ball is lost
const uint8_t LEFT_OUTLANE_SENSOR_PIN = 3;
const uint8_t RIGHT_OUTLANE_SENSOR_PIN = 4;
const uint8_t RAMP_SENSOR_PIN = 5;
const uint8_t TUNNEL_SENSOR_PIN = 6;
const uint8_t LEFT_LANE_SENSOR_PIN = 7;  // top lanes
const uint8_t MIDDLE_LANE_SENSOR_PIN = 8;
const uint8_t RIGHT_LANE_SENSOR_PIN = 9;

// Wheel of fortune
const uint8_t WHEEL_LED_PIN = 13;
const uint8_t BUZZER_PIN = 12;
const uint8_t WHEEL_LED_COUNT = 6;

// ---------------------------------------------------------------------------
// Game settings
// ---------------------------------------------------------------------------

const int BALLS_PER_GAME = 3;

const long BUMPER_POINTS = 100;
const long MIDDLE_LANE_POINTS = 500;
const long SIDE_LANE_POINTS = 200;
const long TARGET_POINTS = 300;
const long WHEEL_SCORE_THRESHOLD = 3000;

const unsigned long SOLENOID_PULSE_MS = 100;
const unsigned long LAUNCH_PULSE_MS = 25;
const unsigned long DRAIN_DEBOUNCE_MS = 300;     // a slow ball must not be counted twice
const unsigned long BALL_RETURN_DELAY_MS = 1500;
const unsigned long LANE_DEBOUNCE_MS = 100;
const unsigned long TARGET_DEBOUNCE_MS = 400;
const unsigned long TARGET_LED_ON_MS = 1000;
const unsigned long GAME_OVER_DELAY_MS = 1200;   // lets the player read the final score

// Wheel of fortune animation
const uint8_t WHEEL_FULL_TURNS = 4;
const float WHEEL_START_STEP_MS = 50.0;
const float WHEEL_SLOWDOWN_FACTOR = 1.08;          // each step is 8 % slower during the full turns
const unsigned long WHEEL_FINAL_STEP_INCREASE_MS = 100;
const unsigned long WHEEL_LIGHT_UP_MS = 800;
const uint8_t WHEEL_BLINK_COUNT = 5;
const unsigned long WHEEL_BLINK_ON_MS = 200;
const unsigned long WHEEL_BLINK_OFF_MS = 800;
const uint8_t WHEEL_MAX_COLOR = 15;                // random colours stay dim
const unsigned int BEEP_FREQUENCY_HZ = 1000;
const unsigned long BEEP_MS = 30;

// LCD layout
const uint8_t LCD_VALUE_COLUMN = 9;
const uint8_t LCD_COLUMNS = 16;

// ---------------------------------------------------------------------------
// Devices and game state
// ---------------------------------------------------------------------------

LiquidCrystal_I2C lcd(0x27, LCD_COLUMNS, 2);
Adafruit_NeoPixel wheel(WHEEL_LED_COUNT, WHEEL_LED_PIN, NEO_GRB + NEO_KHZ800);

long score = 0;  // long: the bonuses can push the score above the 32767 limit of an int
int ballsLeft = BALLS_PER_GAME;
bool ballLost = false;
unsigned long ballLostTime = 0;
bool wheelSpun = false;  // the wheel is spun only once per game

int previousLeftSlingshotSwitch = HIGH;
int previousRightSlingshotSwitch = HIGH;

unsigned long lastDrainTime = 0;
unsigned long lastMiddleLaneTime = 0;
unsigned long lastSideLaneTime = 0;
unsigned long lastTarget2HitTime = 0;
bool target2LedOn = false;

// ---------------------------------------------------------------------------
// Display
// ---------------------------------------------------------------------------

void displayScore() {
  for (uint8_t column = LCD_VALUE_COLUMN; column < LCD_COLUMNS; column++) {
    lcd.setCursor(column, 0);
    lcd.print(' ');
  }
  lcd.setCursor(LCD_VALUE_COLUMN, 0);
  lcd.print(score);
}

void displayBallsLeft() {
  lcd.setCursor(LCD_VALUE_COLUMN, 1);
  lcd.print(' ');
  lcd.setCursor(LCD_VALUE_COLUMN, 1);
  lcd.print(ballsLeft);
}

void addPoints(long points) {
  score += points;
  displayScore();
}

// ---------------------------------------------------------------------------
// Actuators
// ---------------------------------------------------------------------------

void pulseSolenoid(uint8_t pin, unsigned long durationMs) {
  digitalWrite(pin, LOW);  // energise the solenoid
  delay(durationMs);
  digitalWrite(pin, HIGH);  // then release it
}

void beep() {
  tone(BUZZER_PIN, BEEP_FREQUENCY_HZ, BEEP_MS);
  delay(BEEP_MS);
  noTone(BUZZER_PIN);
}

// Lights one wheel LED in a random colour with a beep, waits, then turns it off.
void flashWheelLed(uint8_t led, unsigned long pauseMs) {
  wheel.setPixelColor(led, random(WHEEL_MAX_COLOR), random(WHEEL_MAX_COLOR), random(WHEEL_MAX_COLOR));
  wheel.show();
  beep();
  delay(pauseMs);
  wheel.setPixelColor(led, 0, 0, 0);
  wheel.show();
}

// ---------------------------------------------------------------------------
// Wheel of fortune
// ---------------------------------------------------------------------------

void lightUpWheel() {
  for (uint8_t led = 0; led < WHEEL_LED_COUNT; led++) {
    wheel.setPixelColor(led, 2, 4, 0);
  }
  wheel.show();
  delay(WHEEL_LIGHT_UP_MS);
  wheel.clear();
  wheel.show();
}

void applyWheelReward(uint8_t slot) {
  switch (slot) {
    case 0: score *= 3;      displayScore();     break;
    case 1: ballsLeft += 1;  displayBallsLeft(); break;
    case 2: score += 3000;   displayScore();     break;
    case 3: ballsLeft += 2;  displayBallsLeft(); break;
    case 4: score *= 2;      displayScore();     break;
    case 5: score += 10000;  displayScore();     break;
  }
}

void spinWheel() {
  randomSeed(micros());  // the time at which the player reaches the threshold makes each game different
  const uint8_t finalSlot = random(WHEEL_LED_COUNT);
  float stepMs = WHEEL_START_STEP_MS;

  // Full turns, slowing down a little at each step
  for (uint8_t turn = 0; turn < WHEEL_FULL_TURNS; turn++) {
    for (uint8_t led = 0; led < WHEEL_LED_COUNT; led++) {
      flashWheelLed(led, (unsigned long)stepMs);
      stepMs *= WHEEL_SLOWDOWN_FACTOR;
    }
  }

  // Last, slower turn that stops just before the final slot
  for (uint8_t led = 0; led < finalSlot; led++) {
    flashWheelLed(led, (unsigned long)stepMs);
    stepMs += WHEEL_FINAL_STEP_INCREASE_MS;
  }

  // The final slot blinks
  for (uint8_t blink = 0; blink < WHEEL_BLINK_COUNT; blink++) {
    flashWheelLed(finalSlot, WHEEL_BLINK_ON_MS);
    delay(WHEEL_BLINK_OFF_MS);
  }

  Serial.println(finalSlot);
  applyWheelReward(finalSlot);
}

// ---------------------------------------------------------------------------
// Setup and main loop
// ---------------------------------------------------------------------------

void setup() {
  // Set the solenoid outputs HIGH before enabling them, so that no solenoid fires at power-up
  for (uint8_t pin : SOLENOID_PINS) {
    digitalWrite(pin, HIGH);
    pinMode(pin, OUTPUT);
  }

  Serial.begin(115200);  // fast, so that debug prints do not slow the game down

  wheel.begin();
  wheel.clear();
  wheel.show();
  pinMode(BUZZER_PIN, OUTPUT);
  noTone(BUZZER_PIN);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("SCORE:");
  lcd.setCursor(1, 1);
  lcd.print("Balls:");
  displayScore();
  displayBallsLeft();

  pinMode(LEFT_SLINGSHOT_SWITCH_PIN, INPUT_PULLUP);
  pinMode(RIGHT_SLINGSHOT_SWITCH_PIN, INPUT_PULLUP);
  pinMode(LOWER_BUMPER_RING_PIN, INPUT_PULLUP);
  pinMode(UPPER_LEFT_BUMPER_RING_PIN, INPUT_PULLUP);
  pinMode(UPPER_RIGHT_BUMPER_RING_PIN, INPUT_PULLUP);

  pinMode(TARGET1_PIN, INPUT_PULLUP);
  pinMode(TARGET2_PIN, INPUT_PULLUP);
  pinMode(TARGET1_LED_PIN, OUTPUT);
  pinMode(TARGET2_LED_PIN, OUTPUT);
  digitalWrite(TARGET1_LED_PIN, LOW);
  digitalWrite(TARGET2_LED_PIN, LOW);

  pinMode(DRAIN_SENSOR_PIN, INPUT);
  pinMode(LEFT_OUTLANE_SENSOR_PIN, INPUT);
  pinMode(RIGHT_OUTLANE_SENSOR_PIN, INPUT);
  pinMode(RAMP_SENSOR_PIN, INPUT);
  pinMode(TUNNEL_SENSOR_PIN, INPUT);
  pinMode(LEFT_LANE_SENSOR_PIN, INPUT);
  pinMode(MIDDLE_LANE_SENSOR_PIN, INPUT);
  pinMode(RIGHT_LANE_SENSOR_PIN, INPUT);
}

void loop() {
  const int leftSlingshotSwitch = digitalRead(LEFT_SLINGSHOT_SWITCH_PIN);
  const int rightSlingshotSwitch = digitalRead(RIGHT_SLINGSHOT_SWITCH_PIN);
  const int lowerBumperRing = digitalRead(LOWER_BUMPER_RING_PIN);
  const int upperLeftBumperRing = digitalRead(UPPER_LEFT_BUMPER_RING_PIN);
  const int upperRightBumperRing = digitalRead(UPPER_RIGHT_BUMPER_RING_PIN);

  // Slingshots fire once per press: only on the falling edge of their switch
  if (leftSlingshotSwitch == LOW && previousLeftSlingshotSwitch == HIGH) {
    pulseSolenoid(LEFT_SLINGSHOT_PIN, SOLENOID_PULSE_MS);
  }
  if (rightSlingshotSwitch == LOW && previousRightSlingshotSwitch == HIGH) {
    pulseSolenoid(RIGHT_SLINGSHOT_PIN, SOLENOID_PULSE_MS);
  }
  previousLeftSlingshotSwitch = leftSlingshotSwitch;
  previousRightSlingshotSwitch = rightSlingshotSwitch;

  // Bumpers score and kick the ball back while it touches their ring
  if (lowerBumperRing == LOW) {
    addPoints(BUMPER_POINTS);
    pulseSolenoid(LOWER_BUMPER_PIN, SOLENOID_PULSE_MS);
  }
  if (upperLeftBumperRing == LOW) {
    addPoints(BUMPER_POINTS);
    pulseSolenoid(UPPER_LEFT_BUMPER_PIN, SOLENOID_PULSE_MS);
  }
  if (upperRightBumperRing == LOW) {
    addPoints(BUMPER_POINTS);
    pulseSolenoid(UPPER_RIGHT_BUMPER_PIN, SOLENOID_PULSE_MS);
  }

  // A drained ball is sent back to the launch lane after a short delay
  if (digitalRead(DRAIN_SENSOR_PIN) == LOW && millis() - lastDrainTime >= DRAIN_DEBOUNCE_MS) {
    ballLost = true;
    ballLostTime = millis();
    lastDrainTime = ballLostTime;
  }
  if (ballLost && millis() - ballLostTime >= BALL_RETURN_DELAY_MS) {
    ballsLeft--;
    displayBallsLeft();
    ballLost = false;
    pulseSolenoid(LAUNCH_SOLENOID_PIN, LAUNCH_PULSE_MS);
  }

  // Top lanes
  if (digitalRead(MIDDLE_LANE_SENSOR_PIN) == LOW && millis() - lastMiddleLaneTime >= LANE_DEBOUNCE_MS) {
    addPoints(MIDDLE_LANE_POINTS);
    lastMiddleLaneTime = millis();
  }
  if ((digitalRead(LEFT_LANE_SENSOR_PIN) == LOW || digitalRead(RIGHT_LANE_SENSOR_PIN) == LOW) &&
      millis() - lastSideLaneTime >= LANE_DEBOUNCE_MS) {
    addPoints(SIDE_LANE_POINTS);
    lastSideLaneTime = millis();
  }

  // Game over: show the final score for a moment, then start a new game
  if (ballsLeft == 0) {
    delay(GAME_OVER_DELAY_MS);
    score = 0;
    wheelSpun = false;
    displayScore();
    ballsLeft = BALLS_PER_GAME;
    displayBallsLeft();
  }

  // Target: score and light its LED, then turn the LED off after TARGET_LED_ON_MS
  if (digitalRead(TARGET2_PIN) == LOW && millis() - lastTarget2HitTime >= TARGET_DEBOUNCE_MS) {
    addPoints(TARGET_POINTS);
    digitalWrite(TARGET2_LED_PIN, HIGH);
    target2LedOn = true;
    lastTarget2HitTime = millis();
  }
  if (target2LedOn && millis() - lastTarget2HitTime >= TARGET_LED_ON_MS) {
    digitalWrite(TARGET2_LED_PIN, LOW);
    target2LedOn = false;
  }

  // Wheel of fortune bonus, once per game
  if (score >= WHEEL_SCORE_THRESHOLD && !wheelSpun) {
    wheelSpun = true;
    lightUpWheel();
    spinWheel();
  }
}
