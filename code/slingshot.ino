// Programme de test d'un slingshot : envoie une tension pendant un très court instant au solénoid lorsque le bouton est appuyé.
// à la difference du flipper, le solenoid du slingshot se rétracte immédiatement et ne reste pas activé si le l'interrupteur reste fermé.

const int SLINGSHOT1 = 2;
const int INTERRUPTEUR1 = 3;
int valeurInterrupteur = 1;
int ancienneValeurInterrupteur = 1;

void setup() {
  pinMode(SLINGSHOT1, OUTPUT);
  pinMode(INTERRUPTEUR1, INPUT_PULLUP);
  Serial.begin(9600);
  digitalWrite(SLINGSHOT1, HIGH);
}

void loop() {
  valeurInterrupteur = digitalRead(INTERRUPTEUR1);
  Serial.println(valeurInterrupteur);
  Serial.println(ancienneValeurInterrupteur);  
  if (valeurInterrupteur==LOW && ancienneValeurInterrupteur==HIGH){ //si le bouton est enfoncé et qu'il n'était pas déjà enfoncé à l'instant d'avant
    digitalWrite(SLINGSHOT1, LOW); //on active le solenoide
    delay(50);
    digitalWrite(SLINGSHOT1, HIGH); // puis le solenoide se rétracte immédiatement
  }
  ancienneValeurInterrupteur=valeurInterrupteur;
}
