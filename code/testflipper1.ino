// Programme de test d'un flipper : envoie une tension au solénoïde lorsque le bouton est appuyé.

const int FLIPPER1 = 2;
const int BOUTON1 = 4;
int valeurBouton = 0;

void setup() {
  pinMode(FLIPPER1, OUTPUT);
  pinMode(BOUTON1, INPUT_PULLUP);
  Serial.begin(9600);
  digitalWrite(FLIPPER1, LOW);
}

void loop() {
  valeurBouton = digitalRead(BOUTON1);
  Serial.println(valeurBouton);
  if (valeurBouton==LOW){ //si le bouton est enfoncé
    digitalWrite(FLIPPER1, LOW); //on active le solenoide
  }
  else{
    digitalWrite(FLIPPER1, HIGH);
  }
}
