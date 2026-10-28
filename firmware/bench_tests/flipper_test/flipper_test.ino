// Flipper test: the flipper solenoid stays energised while the button is pressed.
// The solenoid is driven through a relay module that is active LOW.

const uint8_t FLIPPER_SOLENOID_PIN = 2;
const uint8_t BUTTON_PIN = 4;

void setup() {
  pinMode(FLIPPER_SOLENOID_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  digitalWrite(FLIPPER_SOLENOID_PIN, LOW);
}

void loop() {
  const int button = digitalRead(BUTTON_PIN);
  Serial.println(button);
  // Button pressed (LOW): energise the solenoid; released: let it go
  digitalWrite(FLIPPER_SOLENOID_PIN, button == LOW ? LOW : HIGH);
}
