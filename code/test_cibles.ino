const int CIBLE1 = 7;
const int CIBLE2 = 9;
const int LED_CIBLE1=6;
const int LED_CIBLE2=8;
int valeur_cible1;
int valeur_cible2;
int anciennevaleur_cible1 =1;
int anciennevaleur_cible2 =1;
int score;
unsigned long dernierImpactCible1 = 0;
unsigned long dernierImpactCible2 = 0;

void setup() {
  Serial.begin(115200);
  pinMode(CIBLE1, INPUT_PULLUP);
  pinMode(CIBLE2, INPUT_PULLUP);
  pinMode(LED_CIBLE1,OUTPUT);
  pinMode(LED_CIBLE2,OUTPUT);
  digitalWrite(LED_CIBLE1,LOW);
  digitalWrite(LED_CIBLE2,LOW);
}

void loop() {
  valeur_cible1 = digitalRead(CIBLE1);
  valeur_cible2 = digitalRead(CIBLE2);
  if(valeur_cible1 == LOW && anciennevaleur_cible1 == HIGH && millis()-dernierImpactCible1>=400){
     score+=300;
     digitalWrite(LED_CIBLE1, HIGH);
     delay(300);
     digitalWrite(LED_CIBLE1,LOW);
     dernierImpactCible1 = millis();
  }
  if(valeur_cible2 == LOW && anciennevaleur_cible2 == HIGH && millis()-dernierImpactCible2>=400){
     score+=300;
     digitalWrite(LED_CIBLE2, HIGH);
     delay(300);
     digitalWrite(LED_CIBLE2,LOW);
     dernierImpactCible2 = millis();
  }
}
