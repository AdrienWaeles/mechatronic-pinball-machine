// Permet de compter le nombre de passages de la bille devant le capteur infrarouge

const int infrarouge1= 10;
int nombrePassages = 0;
unsigned long dernierPassage = 0;
unsigned long temps = 100; // Contiendra le temps écoulé depuis le début du programme

void setup(){
  pinMode(infrarouge1,INPUT);
  Serial.begin(9600); // vitesse de communication avec l'arduino
}

void loop(){
  // On teste si le capteur infrarouge détecte un passage 
  // et on s'assure qu'aucun objet n'ait été détecté moins de 100millisecondes plus tôt.
  // En effet cela permet d'éviter que une bille passant à faible vitesse devant le capteur comptabilise plusieurs passages
  if (digitalRead(infrarouge1)==LOW && millis()-dernierPassage>=100){ 
    Serial.println("Bille détectée");
    nombrePassages+=1; // Le nombre de passages détectés par le capteur augmente
    dernierPassage = millis(); // Et on sauvegarde le temps écoulé entre le lancement du programme et ce passage
    Serial.print("Nombre de Passages :"); // Finalement on affiche le nombre de passages sur le moniteur série
    Serial.println(nombrePassages);
  }
}
