const int MAX_LVL = 20;
const int lvl=1;
const int led_bleue = 2;
const int led_rouge = 3;
const int led_jaune = 4;
const int led_verte = 5;
const int bouton_bleu = 6;
const int bouton_rouge = 7;
const int bouton_jaune = 8;
const int bouton_vert = 9;
int valeurbouton_bleu;
int valeurbouton_rouge;
int valeurbouton_jaune;
int valeurbouton_vert;
int ordre[MAX_LVL];
int ma_combinaison[MAX_LVL];
int drapeau = 0;

void setup() {
  Serial.begin(9600);
  pinMode(bouton_bleu,INPUT);
  pinMode(bouton_rouge,INPUT);
  pinMode(bouton_jaune,INPUT);
  pinMode(bouton_vert,INPUT);
  pinMode(led_bleue,OUTPUT);
  pinMode(led_rouge,OUTPUT);
  pinMode(led_jaune,OUTPUT);
  pinMode(led_verte,OUTPUT);
  digitalWrite(led_bleue,HIGH);
  digitalWrite(led_rouge,HIGH);
  digitalWrite(led_jaune,HIGH);
  digitalWrite(led_verte,HIGH);
  debut_partie();
}

void sequence_hasard(){
  randomSeed(analogRead(0));
  for (int i=0; i<MAX_LVL; i++){
    ordre[i] = random(2,6);
  }
}

void suite_couleur(int lvl){
  for (int index=0; index<=lvl-1; index++){
      digitalWrite(ordre[index],LOW);
      delay(1000);
      digitalWrite(ordre[index],HIGH);
      delay(500);
  }
}

void jeu(){
  for (lvl=1; lvl<=MAX_LVL; lvl++){
      suite_couleur(lvl);
      delay(2000);
  }
}

void debut_partie(){
  sequence_hasard();
  jeu();
}

void mauvaise_sequence(){
}

void bonne_sequence(){
}

void loop() {
}
