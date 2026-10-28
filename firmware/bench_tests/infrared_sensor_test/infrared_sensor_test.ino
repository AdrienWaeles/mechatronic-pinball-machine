// Infrared sensor test: counts how many times the ball passes in front of the sensor.

const uint8_t IR_SENSOR_PIN = 10;
const unsigned long DEBOUNCE_MS = 100;  // a slow ball must not be counted twice

unsigned int passCount = 0;
unsigned long lastPassTime = 0;

void setup() {
  pinMode(IR_SENSOR_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  // The sensor output is LOW while the ball is in front of it
  if (digitalRead(IR_SENSOR_PIN) == LOW && millis() - lastPassTime >= DEBOUNCE_MS) {
    passCount++;
    lastPassTime = millis();
    Serial.println("Ball detected");
    Serial.print("Number of passes: ");
    Serial.println(passCount);
  }
}
