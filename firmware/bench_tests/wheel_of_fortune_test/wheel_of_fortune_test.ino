// Wheel of fortune test: six NeoPixel LEDs light up one after the other with a beep,
// slow down, stop on a random LED and make it blink.

#include <Adafruit_NeoPixel.h>

const uint8_t WHEEL_LED_PIN = 6;
const uint8_t BUZZER_PIN = 2;
const uint8_t WHEEL_LED_COUNT = 6;

const uint8_t FULL_TURNS = 3;
const unsigned long START_STEP_MS = 150;
const unsigned long FINAL_STEP_INCREASE_MS = 100;
const uint8_t BLINK_COUNT = 5;
const unsigned long BLINK_ON_MS = 200;
const unsigned long BLINK_OFF_MS = 800;
const unsigned long PAUSE_BETWEEN_SPINS_MS = 2000;
const uint8_t MAX_COLOR = 22;

Adafruit_NeoPixel wheel(WHEEL_LED_COUNT, WHEEL_LED_PIN, NEO_GRB + NEO_KHZ800);

void setRandomColor(uint8_t led) {
  wheel.setPixelColor(led, random(MAX_COLOR), random(MAX_COLOR), random(MAX_COLOR));
  wheel.show();
}

void turnOff(uint8_t led) {
  wheel.setPixelColor(led, 0, 0, 0);
  wheel.show();
}

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  wheel.begin();
  wheel.show();  // all LEDs off
  digitalWrite(BUZZER_PIN, HIGH);
}

void loop() {
  const uint8_t finalSlot = random(WHEEL_LED_COUNT);
  unsigned long stepMs = START_STEP_MS;

  for (uint8_t turn = 0; turn < FULL_TURNS; turn++) {
    for (uint8_t led = 0; led < WHEEL_LED_COUNT; led++) {
      setRandomColor(led);
      tone(BUZZER_PIN, 1000, stepMs);
      delay(stepMs);
      noTone(BUZZER_PIN);
      turnOff(led);
    }
  }

  for (uint8_t led = 0; led < finalSlot; led++) {
    setRandomColor(led);
    tone(BUZZER_PIN, 1000, stepMs);
    delay(stepMs);
    digitalWrite(BUZZER_PIN, HIGH);
    turnOff(led);
    stepMs += FINAL_STEP_INCREASE_MS;
  }

  for (uint8_t blink = 0; blink < BLINK_COUNT; blink++) {
    setRandomColor(finalSlot);
    tone(BUZZER_PIN, 293, BLINK_ON_MS);
    delay(BLINK_ON_MS);
    digitalWrite(BUZZER_PIN, HIGH);
    turnOff(finalSlot);
    delay(BLINK_OFF_MS);
  }

  delay(PAUSE_BETWEEN_SPINS_MS);
}
