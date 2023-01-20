#include "Wire.h"
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C LCD(0x27,16,2); // définit le type d'écran lcd 16 x 2

void setup() {
  LCD.init(); // initialisation de l'afficheur
  LCD.backlight();
  
  LCD.setCursor(1, 0);
  LCD.print("SCORE :");

  LCD.setCursor(10, 1);
  LCD.print("POINTS");
  LCD.display();
  LCD.setCursor(1, 1);
}

void loop() {
  for (int i=0; i<1000; i++){
    LCD.setCursor(1, 0);
    LCD.print("SCORE :");
    LCD.setCursor(10, 1);
    LCD.print("POINTS");
    LCD.setCursor(1, 1);    
    LCD.print(i);
    delay(1000);
    LCD.clear();
  }
   
}

