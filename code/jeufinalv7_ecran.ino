// ECRAN
#include "Wire.h"
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C LCD(0x27,16,2); // définit le type d'écran lcd 16 x 2


// Solenoides :
const int SOLENOIDE_LANCEMENT = 48;
const int SLINGSHOTG = 42; // slingshot gauche
const int SLINGSHOTD = 44; //slingshot droit
const int BUMPER_BAS = 46;
const int BUMPER_HAUTG = 52; // bumper gauche supérieur
const int BUMPER_HAUTD = 50; // bumper droit supérieur
const int solenoides[6] = { SOLENOIDE_LANCEMENT, SLINGSHOTG, SLINGSHOTD, BUMPER_BAS, BUMPER_HAUTG, BUMPER_HAUTD}; // liste contenant tous les pattes de branchement des solénoides

// Micro switches des slingshots :
const int SWITCH_SLINGSHOTG = A1;
const int SWITCH_SLINGSHOTD = A0;

// Anneaux des bumpers :
const int ANNEAU_BUMPER_BAS = 26;
const int ANNEAU_BUMPER_HAUTG = 24; 
const int ANNEAU_BUMPER_HAUTD = 22;

// Micro switches des cibles :
const int CIBLE1 = 31;
const int CIBLE2 = 37;
const int LED_CIBLE1=33;
const int LED_CIBLE2=35;

// Capteurs infrarouges
const int IR_SORTIEM = 2; // détecte si le joueur a perdu la bille entre ses 2 flippers
const int IR_SORTIEG = 3; // IR permettant de détecter si le joueur a perdu la bille sur la sortie gauche
const int IR_SORTIED = 4; // sortie droite
const int IR_RAMPE = 5;
const int IR_TUNNEL = 6;
const int IR_COLONNEG = 7; // IR de la rangée gauche du haut de flipper
const int IR_COLONNEM = 8; // rangée du milieu
const int IR_COLONNED =9; // rangée droite

// ROUE DE LA FORTUNE
int nombreLeds =6;
int nombreTours = 5;
int casefinale;
float tempsPause=50.0;
int dureeBip = 30;
int buzzer=13;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(nombreLeds, 6, NEO_GRB + NEO_KHZ800);

// Valeurs lues sur les interrupteurs des slingshots
int valeur_slingshotG;
int valeur_slingshotD;
int anciennevaleur_slingshotG =1;
int anciennevaleur_slingshotD =1;

// Valeurs lues sur les anneaux des bumpers
int valeur_anneau_bumperbas;
int valeur_anneau_bumperhautG;
int valeur_anneau_bumperhautD;

// Valeurs lues sur les interrupteurs des cibles :
int valeur_cible1;
int valeur_cible2;
int anciennevaleur_cible1 =1;
int anciennevaleur_cible2 =1;
// stockent le temps écoulé depuis le début du programme jusqu'au dernier moment où les cibles ont été touchées 
unsigned long dernierImpactCible1 = 0; 
unsigned long dernierImpactCible2 = 0;

boolean led_cible1_allumee = false; // permet de mémoriser si l'on a allumé la led afin de l'éteindre plus tard sans delay avec millis

boolean led_cible2_allumee = false;


// Variable permettant de mémoriser à quel moment un capteur a détecté le précédent passage
unsigned long dernierPassageIR_sortieM = 0;
unsigned long dernierPassageIR_sortieG = 0;
unsigned long dernierPassageIR_sortieD = 0;
unsigned long dernierPassageIR_rampe = 0;
unsigned long dernierPassageIR_tunnel = 0;
unsigned long dernierPassageIR_colonneGD = 0;
unsigned long dernierPassageIR_colonneM = 0;

// Variables permettant d'enregistrer le score et le nombre de billes restantes
int score = 0;
int nombre_billes = 3; // nombre de tentatives offertes au joueur (le nombre de lancers de bille qu'il va pouvoir faire)
int billes_restantes = nombre_billes; // tentatives restantes
boolean billeperdue = false; // permet de mémoriser si le joueur a perdu la bille le temps de déclencher un solénoide
unsigned long temps_billeperdue = 0; // stocke le moment auquel le joueur a perdu la bille

void setup() {
  Serial.begin(115200); // Vitesse de communication avec l'arduino (volontairement élévée car sinon ralentit la fluidité du jeu)

  // ECRAN
  LCD.init(); // initialisation de l'afficheur
  LCD.backlight();
  LCD.setCursor(1, 0);
  LCD.print("SCORE:");
  LCD.setCursor(1, 1);
  LCD.print("Billes: ");
  afficheScore(score); // on affiche le score de début de partie (normalement 0)
  afficheNombreBilles(nombre_billes); // et le nombre de billes (tentatives) au début
  
  pinMode(SOLENOIDE_LANCEMENT, OUTPUT);
  pinMode(SLINGSHOTG, OUTPUT);
  pinMode(SLINGSHOTD, OUTPUT);
  pinMode(BUMPER_BAS, OUTPUT);
  pinMode(BUMPER_HAUTG, OUTPUT);
  pinMode(BUMPER_HAUTD, OUTPUT);

// Les interrupteurs utilisent la résistance de rappel de l'arduino
  pinMode(SWITCH_SLINGSHOTG, INPUT_PULLUP);
  pinMode(SWITCH_SLINGSHOTD, INPUT_PULLUP);
  pinMode(ANNEAU_BUMPER_BAS, INPUT_PULLUP);
  pinMode(ANNEAU_BUMPER_HAUTG, INPUT_PULLUP);
  pinMode(ANNEAU_BUMPER_HAUTD, INPUT_PULLUP);;

  // cibles
  pinMode(CIBLE1, INPUT_PULLUP);
  pinMode(CIBLE2, INPUT_PULLUP);
  pinMode(LED_CIBLE1,OUTPUT);
  pinMode(LED_CIBLE2,OUTPUT);
  // on éteint les leds des cibles au début du jeu
  digitalWrite(LED_CIBLE1,LOW);
  digitalWrite(LED_CIBLE2,LOW);
  
  pinMode(IR_SORTIEG, INPUT);
  pinMode(IR_SORTIEM, INPUT);
  pinMode(IR_SORTIED, INPUT);
  pinMode(IR_COLONNEG, INPUT);
  pinMode(IR_COLONNEM, INPUT);
  pinMode(IR_COLONNED, INPUT);
  pinMode(IR_RAMPE, INPUT);
  pinMode(IR_TUNNEL, INPUT);

  // On s'assure que tous les solénoides ne sont pas alimentés au début du jeu
  for (int i=0; i<6; i++){
    digitalWrite(solenoides[i], HIGH);
  }
}

// FONCTIONS D'AFFICHAGE ECRAN 
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
  // On lit les valeurs des anneaux et microswitches
  valeur_slingshotG = digitalRead(SWITCH_SLINGSHOTG);
  valeur_slingshotD = digitalRead(SWITCH_SLINGSHOTD);
  valeur_anneau_bumperbas = digitalRead(ANNEAU_BUMPER_BAS);
  valeur_anneau_bumperhautG = digitalRead(ANNEAU_BUMPER_HAUTG);
  valeur_anneau_bumperhautD = digitalRead(ANNEAU_BUMPER_HAUTD);

  // Activation des slingshots slingshots
  if (valeur_slingshotG == LOW && anciennevaleur_slingshotG == HIGH){
    digitalWrite(SLINGSHOTG, LOW); // On active le solenoide
    delay(100);
    digitalWrite(SLINGSHOTG, HIGH); // puis le solenoide se rétracte presque immédiatement
  }
  if (valeur_slingshotD == LOW && anciennevaleur_slingshotD == HIGH){
    digitalWrite(SLINGSHOTD, LOW);
    delay(100);
    digitalWrite(SLINGSHOTD, HIGH);
  }

  // on stocke la valeur actuelle des interrupteur pour éviter un effet rebond
  anciennevaleur_slingshotG = valeur_slingshotG;
  anciennevaleur_slingshotD = valeur_slingshotD;

  // Activation des bumpers
  if (valeur_anneau_bumperbas == LOW){
    score+=100;
    afficheScore(score);
    digitalWrite(BUMPER_BAS, LOW); // On active le solenoide
    delay(100);
    digitalWrite(BUMPER_BAS, HIGH); // puis le solenoide se rétracte presque immédiatement
  }

  if (valeur_anneau_bumperhautG == LOW){
    score+=100;
    afficheScore(score);
    digitalWrite(BUMPER_HAUTG, LOW); 
    delay(100);
    digitalWrite(BUMPER_HAUTG, HIGH);
  }

  if (valeur_anneau_bumperhautD == LOW){
    score+=100;
    afficheScore(score);
    digitalWrite(BUMPER_HAUTD, LOW); 
    delay(100);
    digitalWrite(BUMPER_HAUTD, HIGH); 
  }

  // Détection de passages de la bille avec les Capteurs Infrarouges
  
  // On teste si le capteur IR détecte un passage et on s'assure qu'aucun objet n'ait été détecté moins de 300 millisecondes plus tôt.
  // Cela permet d'éviter qu'une bille passant à faible vitesse devant le capteur comptabilise plusieurs passages
  if ( (digitalRead(IR_SORTIEM)==LOW )&& millis()-dernierPassageIR_sortieM>=300){ 
    billeperdue = true;
    temps_billeperdue = millis();
    dernierPassageIR_sortieM = millis(); // Et on sauvegarde le temps écoulé entre le lancement du programme et ce passage
  }

  // Si la bille est perdue on attend 1,5 secondes et on active un solenoide permettant de la ramener dans la zone de lancement
  if (billeperdue && millis()-temps_billeperdue>=1500){
    billes_restantes -=1;
    afficheNombreBilles(billes_restantes);
    billeperdue=false; // la bille n'est plus perdue puisque on a réduit le nombre de billes (tentatives restantes).
    digitalWrite(SOLENOIDE_LANCEMENT, LOW);
    delay(25);
    digitalWrite(SOLENOIDE_LANCEMENT, HIGH);
  }

  // COLONNES A POINTS (on ajoute un certain nombre de points en fonction de là ou passe la bille)
  if ( (digitalRead(IR_COLONNEM)==LOW )&& millis()-dernierPassageIR_colonneM>=100){ 
    score+=500;
    afficheScore(score);
    dernierPassageIR_colonneM = millis();
  }
  
  if ( (digitalRead(IR_COLONNEG)==LOW || (digitalRead(IR_COLONNED)==LOW ))&& millis()-dernierPassageIR_colonneGD>=100){ 
    score+=200;
    afficheScore(score);
    dernierPassageIR_colonneGD = millis();
  }
  
  Serial.println(score);
  Serial.print("Billes restantes :");
  Serial.println(billes_restantes);

  // Lorsque le joueur a perdu toutes ses tentatives
  if (billes_restantes==0){
    delay(1200); // on attend un peu afin que le joueur puisse voir son score
    // et on rénitialise la partie :
    score=0;
    billes_restantes = 3;
    afficheNombreBilles(billes_restantes);
  }

  // Si une cible est touchée on allume sa led et on ajoute des points au score
  // millis permet d'éviter l'effet rebond du microswitch
  //valeur_cible1 = digitalRead(CIBLE1);
  valeur_cible2 = digitalRead(CIBLE2);
  /*if(valeur_cible1 == LOW && anciennevaleur_cible1 == HIGH && millis()-dernierImpactCible1>=400){
     score+=300;
     digitalWrite(LED_CIBLE1, LOW);
     delay(300);
     digitalWrite(LED_CIBLE1, HIGH);
     led_cible1_allumee = true;
     dernierImpactCible1 = millis();
  }
  */
  if(valeur_cible2 == LOW && millis()-dernierImpactCible2>=400){
     score+=300;
     afficheScore(score);
     digitalWrite(LED_CIBLE2, HIGH);
     led_cible2_allumee = true;
     dernierImpactCible2 = millis();
  }
  /*
  if (led_cible1_allumee && led_cible2_allumee && millis-max(dernierImpactCible1,dernierImpactCible2)>=300 ){ // on éteint la led de la cible 300millisecondes après l'avoir allumé
    digitalWrite(LED_CIBLE1,LOW);
    digitalWrite(LED_CIBLE2,LOW);
    led_cible1_allumee = false;
    led_cible2_allumee = false;
  }
  */

  if (led_cible2_allumee && millis-dernierImpactCible2>=1000 ){ // on éteint la led de la cible 300millisecondes après l'avoir allumé
    //digitalWrite(LED_CIBLE1,LOW);
    digitalWrite(LED_CIBLE2,LOW);
    //led_cible1_allumee = false;
    led_cible2_allumee = false;
  }
  
}