#include <Adafruit_NeoPixel.h>

int nombreLeds =6;
int nombreTours = 4;
int casefinale;
int tempsPause=150;

int buzzer=2;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(nombreLeds, 6, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(buzzer, OUTPUT);
  strip.begin();
  strip.show(); // Initialise toute les led à 'off'
  digitalWrite(2, HIGH);
}

void loop() {
  casefinale = random(0, nombreLeds);
  for(int tour=1; tour<nombreTours; tour++){
    for (int led=0; led<nombreLeds; led++){
      strip.setPixelColor(led, random(0, 22), random(0, 22), random(0, 22));
      strip.show(); // on affiche 
      tone(buzzer,1000,150);
      delay(tempsPause);
      noTone(buzzer);

      strip.setPixelColor(led, 0, 0, 0);
      strip.show();
    }
  }
  for (int led=0; led<casefinale; led++){
      strip.setPixelColor(led, random(0, 22), random(0, 22), random(0, 22));
      strip.show(); // on affiche
      tone(buzzer,1000,tempsPause);
      delay(tempsPause);
      digitalWrite(2, HIGH);
      strip.setPixelColor(led, 0, 0, 0);
      strip.show();
      tempsPause+=100;
  }
  for (int clignote=0; clignote<5; clignote++){
      strip.setPixelColor(casefinale, random(0, 22), random(0, 22), random(0, 22));
      strip.show(); // on affiche
      tone(buzzer,293,200);
      delay(200);
      digitalWrite(2, HIGH);
      strip.setPixelColor(casefinale, 0, 0, 0);
      strip.show();
      delay(800);
  }
  delay(2000);
  tempsPause = 150;
}
