const int SOLENOIDE_LANCEMENT = 48;
const int SLINGSHOTG = 42; // slingshot gauche
const int SLINGSHOTD = 44; //slingshot droit
const int BUMPER_BAS = 46;
const int BUMPER_HAUTG = 52; // bumper gauche supérieur
const int BUMPER_HAUTD = 50; // bumper droit supérieur

const int solenoides[6] = { SOLENOIDE_LANCEMENT, SLINGSHOTG, SLINGSHOTD, BUMPER_BAS, BUMPER_HAUTG, BUMPER_HAUTD};

const int SWITCH_SLINGSHOTG = A1;
const int SWITCH_SLINGSHOTD = A0;

const int ANNEAU_BUMPER_BAS = 26;
const int ANNEAU_BUMPER_HAUTG = 24; 
const int ANNEAU_BUMPER_HAUTD = 22;

// Infrarouges
const int IR_SORTIEM = 2; // détecte si le joueur a perdu la bille entre ses 2 flippers
const int IR_SORTIEG = 3; // IR permettant de détecter si le joueur a perdu la bille sur la sortie gauche
const int IR_SORTIED = 4; // sortie droite
const int IR_RAMPE = 5;
const int IR_TUNNEL = 6;
const int IR_COLONNEG = 7; // IR de la rangée gauche du haut de flipper
const int IR_COLONNEM = 8; // rangée du milieu
const int IR_COLONNED =9; // rangée droite

int valeur_slingshotG;
int valeur_slingshotD;
int anciennevaleur_slingshotG =1;
int anciennevaleur_slingshotD =1;

int valeur_anneau_bumperbas;
int valeur_anneau_bumperhautG;
int valeur_anneau_bumperhautD;

unsigned long dernierPassageIR_sortieM = 0;
unsigned long dernierPassageIR_sortieG = 0;
unsigned long dernierPassageIR_sortieD = 0;
unsigned long dernierPassageIR_rampe = 0;
unsigned long dernierPassageIR_tunnel = 0;
unsigned long dernierPassageIR_colonneGD = 0;
unsigned long dernierPassageIR_colonneM = 0;
unsigned long temps = 100; // Contiendra le temps écoulé depuis le début du programme

int score = 0;
int nombre_billes = 3;
int billes_restantes = nombre_billes;
boolean billeperdue = false;
unsigned long temps_billeperdue = 0;

void setup() {
  Serial.begin(115000);
  
  pinMode(SOLENOIDE_LANCEMENT, OUTPUT);
  pinMode(SLINGSHOTG, OUTPUT);
  pinMode(SLINGSHOTD, OUTPUT);
  pinMode(BUMPER_BAS, OUTPUT);
  pinMode(BUMPER_HAUTG, OUTPUT);
  pinMode(BUMPER_HAUTD, OUTPUT);

  pinMode(SWITCH_SLINGSHOTG, INPUT_PULLUP);
  pinMode(SWITCH_SLINGSHOTD, INPUT_PULLUP);
  pinMode(ANNEAU_BUMPER_BAS, INPUT_PULLUP);
  pinMode(ANNEAU_BUMPER_HAUTG, INPUT_PULLUP);
  pinMode(ANNEAU_BUMPER_HAUTD, INPUT_PULLUP);;
  
  pinMode(IR_SORTIEG, INPUT);
  pinMode(IR_SORTIEM, INPUT);
  pinMode(IR_SORTIED, INPUT);
  pinMode(IR_COLONNEG, INPUT);
  pinMode(IR_COLONNEM, INPUT);
  pinMode(IR_COLONNED, INPUT);
  pinMode(IR_RAMPE, INPUT);
  pinMode(IR_TUNNEL, INPUT);

  for (int i=0; i<6; i++){
    digitalWrite(solenoides[i], HIGH);
  }
}

void loop() {
  // On lit les valeurs des anneaux et microswitches
  valeur_slingshotG = digitalRead(SWITCH_SLINGSHOTG);
  valeur_slingshotD = digitalRead(SWITCH_SLINGSHOTD);
  valeur_anneau_bumperbas = digitalRead(ANNEAU_BUMPER_BAS);
  valeur_anneau_bumperhautG = digitalRead(ANNEAU_BUMPER_HAUTG);
  valeur_anneau_bumperhautD = digitalRead(ANNEAU_BUMPER_HAUTD);

  // Microswitches des slintgshots
  if (valeur_slingshotG == LOW && anciennevaleur_slingshotG == HIGH){
    digitalWrite(SLINGSHOTG, LOW); // On active le solenoide
    delay(100);
    digitalWrite(SLINGSHOTG, HIGH); // puis le solenoide se rétracte presque immédiatement
  }
  if (valeur_slingshotD == LOW && anciennevaleur_slingshotD == HIGH){
    digitalWrite(SLINGSHOTD, LOW); // On active le solenoide
    delay(100);
    digitalWrite(SLINGSHOTD, HIGH); // puis le solenoide se rétracte presque immédiatement
  }

  anciennevaleur_slingshotG = valeur_slingshotG;
  anciennevaleur_slingshotD = valeur_slingshotD;

  // Anneaux des bumpers
  if (valeur_anneau_bumperbas == LOW){
    score+=100;
    digitalWrite(BUMPER_BAS, LOW); // On active le solenoide
    delay(100);
    digitalWrite(BUMPER_BAS, HIGH); // puis le solenoide se rétracte presque immédiatement
  }

  if (valeur_anneau_bumperhautG == LOW){
    score+=100;
    digitalWrite(BUMPER_HAUTG, LOW); // On active le solenoide
    delay(100);
    digitalWrite(BUMPER_HAUTG, HIGH); // puis le solenoide se rétracte presque immédiatement
  }

  if (valeur_anneau_bumperhautD == LOW){
    score+=100;
    digitalWrite(BUMPER_HAUTD, LOW); // On active le solenoide
    delay(100);
    digitalWrite(BUMPER_HAUTD, HIGH); // puis le solenoide se rétracte presque immédiatement
  }

    // On teste si le capteur IR détecte un passage et on s'assure qu'aucun objet n'ait été détecté moins de 100millisecondes plus tôt.
  // Cela permet d'éviter qu'une bille passant à faible vitesse devant le capteur comptabilise plusieurs passages
  if ( (digitalRead(IR_SORTIEM)==LOW )&& millis()-dernierPassageIR_sortieM>=300){ 
    billes_restantes -=1;
    billeperdue = true;
    temps_billeperdue = millis();
    dernierPassageIR_sortieM = millis(); // Et on sauvegarde le temps écoulé entre le lancement du programme et ce passage
  }

}
