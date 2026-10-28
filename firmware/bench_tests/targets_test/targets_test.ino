// Targets test: each hit adds points and flashes the target LED.
// A hit is counted on the falling edge of the target switch, at most once every DEBOUNCE_MS.

const uint8_t TARGET1_PIN = 7;
const uint8_t TARGET2_PIN = 9;
const uint8_t TARGET1_LED_PIN = 6;
const uint8_t TARGET2_LED_PIN = 8;

const long TARGET_POINTS = 300;
const unsigned long DEBOUNCE_MS = 400;
const unsigned long LED_FLASH_MS = 300;

long score = 0;
int previousTarget1 = HIGH;
int previousTarget2 = HIGH;
unsigned long lastTarget1HitTime = 0;
unsigned long lastTarget2HitTime = 0;

void flashLed(uint8_t ledPin) {
  digitalWrite(ledPin, HIGH);
  delay(LED_FLASH_MS);
  digitalWrite(ledPin, LOW);
}

void setup() {
  Serial.begin(115200);
  pinMode(TARGET1_PIN, INPUT_PULLUP);
  pinMode(TARGET2_PIN, INPUT_PULLUP);
  pinMode(TARGET1_LED_PIN, OUTPUT);
  pinMode(TARGET2_LED_PIN, OUTPUT);
  digitalWrite(TARGET1_LED_PIN, LOW);
  digitalWrite(TARGET2_LED_PIN, LOW);
}

void loop() {
  const int target1 = digitalRead(TARGET1_PIN);
  const int target2 = digitalRead(TARGET2_PIN);

  if (target1 == LOW && previousTarget1 == HIGH && millis() - lastTarget1HitTime >= DEBOUNCE_MS) {
    score += TARGET_POINTS;
    flashLed(TARGET1_LED_PIN);
    lastTarget1HitTime = millis();
  }
  if (target2 == LOW && previousTarget2 == HIGH && millis() - lastTarget2HitTime >= DEBOUNCE_MS) {
    score += TARGET_POINTS;
    flashLed(TARGET2_LED_PIN);
    lastTarget2HitTime = millis();
  }

  previousTarget1 = target1;
  previousTarget2 = target2;
}
