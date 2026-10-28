// Microswitch test: increments a counter every 100 ms while the switch is closed.

const uint8_t MICROSWITCH_PIN = 3;
const unsigned long SAMPLE_PERIOD_MS = 100;

unsigned long count = 0;

void setup() {
  pinMode(MICROSWITCH_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(MICROSWITCH_PIN) == HIGH) {
    count++;
  }
  Serial.print("count: ");
  Serial.println(count);
  delay(SAMPLE_PERIOD_MS);
}
