// I2C LCD test: counts from 0 to 999 on a 16x2 display, one step per second.

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void showCount(int count) {
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("SCORE :");
  lcd.setCursor(10, 1);
  lcd.print("POINTS");
  lcd.setCursor(1, 1);
  lcd.print(count);
}

void setup() {
  lcd.init();
  lcd.backlight();
}

void loop() {
  for (int count = 0; count < 1000; count++) {
    showCount(count);
    delay(1000);
  }
}
