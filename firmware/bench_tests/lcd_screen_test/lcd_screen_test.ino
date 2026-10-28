#include "Wire.h"
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C LCD(0x27,16,2); // définit le type d'écran lcd 16 x 2

void setup() {
  LCD.init(); // initialisation de l'afficheur
  LCD.backlight();
  LCD.setCursor(1, 0);
  LCD.print("SCORE:");
  LCD.setCursor(1, 1);
  LCD.print("Billes: ");
  afficheScore(0);
  afficheNombreBilles(3);
}

void afficheScore(int score){
  // on efface le score précédent
  for (int i = 9; i < 16; i++)
  {
    LCD.setCursor(i, 0);
    LCD.print(" ");
  }

  // On écrit le nouveau score
  LCD.setCursor(9, 0);
  LCD.print(score);  
}

void afficheNombreBilles(int nombreBilles){
  // on efface le nombre précédent
  LCD.setCursor(9, 1);
  LCD.print(" ");

  // On écrit le nouveau score
  LCD.setCursor(9, 1);
  LCD.print(nombreBilles);  
}


void loop() {
  for (int points=0; points<=500; points+=100){
      afficheScore(points);
      delay(1000);
  }
  for (int nombreBilles = 3; nombreBilles>=0; nombreBilles--){
    afficheNombreBilles(nombreBilles);
    delay(1000);
  }
}
