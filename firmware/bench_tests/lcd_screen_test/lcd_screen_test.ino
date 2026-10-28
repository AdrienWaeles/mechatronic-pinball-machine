// LCD layout test for the game display: shows a score and the number of balls left,
// and updates both every second.

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const uint8_t LCD_VALUE_COLUMN = 9;
const uint8_t LCD_COLUMNS = 16;

LiquidCrystal_I2C lcd(0x27, LCD_COLUMNS, 2);

void displayScore(long score) {
  for (uint8_t column = LCD_VALUE_COLUMN; column < LCD_COLUMNS; column++) {
    lcd.setCursor(column, 0);
    lcd.print(' ');
  }
  lcd.setCursor(LCD_VALUE_COLUMN, 0);
  lcd.print(score);
}

void displayBallsLeft(int balls) {
  lcd.setCursor(LCD_VALUE_COLUMN, 1);
  lcd.print(' ');
  lcd.setCursor(LCD_VALUE_COLUMN, 1);
  lcd.print(balls);
}

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("SCORE:");
  lcd.setCursor(1, 1);
  lcd.print("Balls:");
  displayScore(0);
  displayBallsLeft(3);
}

void loop() {
  for (long points = 0; points <= 500; points += 100) {
    displayScore(points);
    delay(1000);
  }
  for (int balls = 3; balls >= 0; balls--) {
    displayBallsLeft(balls);
    delay(1000);
  }
}
