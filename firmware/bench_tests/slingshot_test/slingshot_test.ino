// Slingshot test: fires the solenoid for a very short time when the switch is pressed.
// Unlike a flipper, the slingshot releases immediately and does not stay energised
// while the switch remains closed: it only fires on the falling edge of the switch.
// The solenoid is driven through a relay module that is active LOW.

const uint8_t SLINGSHOT_SOLENOID_PIN = 2;
const uint8_t SWITCH_PIN = 3;
const unsigned long PULSE_MS = 50;

int previousSwitch = HIGH;

void setup() {
  pinMode(SLINGSHOT_SOLENOID_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  digitalWrite(SLINGSHOT_SOLENOID_PIN, HIGH);
}

void loop() {
  const int currentSwitch = digitalRead(SWITCH_PIN);
  Serial.println(currentSwitch);
  Serial.println(previousSwitch);
  if (currentSwitch == LOW && previousSwitch == HIGH) {
    digitalWrite(SLINGSHOT_SOLENOID_PIN, LOW);  // energise the solenoid
    delay(PULSE_MS);
    digitalWrite(SLINGSHOT_SOLENOID_PIN, HIGH);  // then release it
  }
  previousSwitch = currentSwitch;
}
