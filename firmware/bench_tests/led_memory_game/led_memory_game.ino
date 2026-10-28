// Prototype of a colour memory game: plays a random sequence on four LEDs, one more colour at each level.
// Reading the player's answer on the buttons was not implemented.
// The LEDs are wired active LOW.

const int MAX_LEVEL = 20;

const uint8_t BLUE_LED_PIN = 2;
const uint8_t RED_LED_PIN = 3;
const uint8_t YELLOW_LED_PIN = 4;
const uint8_t GREEN_LED_PIN = 5;
const uint8_t LED_PINS[] = {BLUE_LED_PIN, RED_LED_PIN, YELLOW_LED_PIN, GREEN_LED_PIN};

const uint8_t BLUE_BUTTON_PIN = 6;
const uint8_t RED_BUTTON_PIN = 7;
const uint8_t YELLOW_BUTTON_PIN = 8;
const uint8_t GREEN_BUTTON_PIN = 9;
const uint8_t BUTTON_PINS[] = {BLUE_BUTTON_PIN, RED_BUTTON_PIN, YELLOW_BUTTON_PIN, GREEN_BUTTON_PIN};

const unsigned long LED_ON_MS = 1000;
const unsigned long LED_OFF_MS = 500;
const unsigned long PAUSE_BETWEEN_LEVELS_MS = 2000;

uint8_t sequence[MAX_LEVEL];  // LED pin to light at each step

void generateSequence() {
  randomSeed(analogRead(0));
  for (int step = 0; step < MAX_LEVEL; step++) {
    sequence[step] = LED_PINS[random(4)];
  }
}

void playSequence(int length) {
  for (int step = 0; step < length; step++) {
    digitalWrite(sequence[step], LOW);
    delay(LED_ON_MS);
    digitalWrite(sequence[step], HIGH);
    delay(LED_OFF_MS);
  }
}

void setup() {
  Serial.begin(9600);
  for (uint8_t pin : BUTTON_PINS) {
    pinMode(pin, INPUT);
  }
  for (uint8_t pin : LED_PINS) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
  }

  generateSequence();
  for (int level = 1; level <= MAX_LEVEL; level++) {
    playSequence(level);
    delay(PAUSE_BETWEEN_LEVELS_MS);
  }
}

void loop() {
}
