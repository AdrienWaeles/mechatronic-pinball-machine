// Programme de test d'un flipper : envoie une tension pendant un très court instant au solénoid lorsque le bouton est appuyé.

const int FLIPPER1 = 2;
const int BOUTON1 = 3;
int valeurBouton = 0;

void setup() {
  pinMode(FLIPPER1, OUTPUT);
  pinMode(BOUTON1, INPUT);
  Serial.begin(9600);
  digitalWrite(FLIPPER1, LOW);
}

void loop() {
  valeurBouton = digitalRead(BOUTON1);
  Serial.println(valeurBouton);
  if (valeurBouton==HIGH){ //si le bouton est enfoncé
    digitalWrite(FLIPPER1, HIGH); //on active le solenoid
    delay(10);
    digitalWrite(FLIPPER1, LOW); // puis le solenoid se rétracte immédiatement
  }
}
