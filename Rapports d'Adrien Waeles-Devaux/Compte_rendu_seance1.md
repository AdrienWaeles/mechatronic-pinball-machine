Contenu de cette séance : Flippers imprimés en 3D, test de fonctionnement d’un solénoïde avec bouton et détection de passage d’une bille avec un capteur infrarouge.



Avant la séance : 
Nous avons modélisé en 3d deux pièces pour créer un prototype de flipper, puis je les ai imprimé en 3D afin de pouvoir effectuer des tests le jour de la séance et adapter les pièces en conséquence. La première pièce ci-dessous étant le flipper gauche qui sert à renvoyer la balle sur la planche.  La deuxième pièce (la plus petite sera cachée sous la planche et fixée au moteur), elle permet de transformer le mouvement linéaire d’un solénoïde en un mouvement de rotation. Il faudra ajuster prochainement les dimensions et la forme de cette dernière pièce pour l’adapter au solénoïde choisi.

<img src="Images des rapports/Images séance 1/flipper_sketch3d.jpg" width="300">

<img src="flipper_impression3d.jpg" width="300">



Durant la séance :
Test de fonctionnement du solénoïde JF-0730B (12V, 1A, déplacement de 10mm).
Étant donné que le solénoïde nécessite d’être alimenté avec une tension de 12V, il nécessite une alimentation externe, afin de ne pas endommager la carte arduino, pour cela j’ai ajouté au circuit un relais commutateur. 
Documentation du relais commutateur JQC-3FF-S-Z : 
![imageflipper](documentation_relais_commutateur.jpg)

Le relais commutateur se comporte comme un interrupteur qui est commandé par l’arduino. Ainsi lorsque l’interrupteur est fermé le solénoïde sera alimenté par l’alimentation externe (ici alimentation 12V) et lorsque l’interrupteur est ouvert le solénoïde n’est plus alimenté. Pour ouvrir ou fermer l’interrupteur on envoie un signal numérique depuis l’Arduino. Ainsi on évite de faire trop chauffer le solénoide puisqu’il n’est alimenté que lorsque l’on appuie sur le bouton.

Le programme réalisé est le suivant : ![imageflipper](programme_flipper+bouton.jpg)

Voici le fonctionnement de ce premier test en vidéo :
https://www.youtube.com/watch?v=6iraHV_b1UE


Résultat des tests et des recherches : le petit solénoïde 12V utilisé ne semble pas suffisant pour faire bouger avec assez de force les flippers, la balle risque de ne pas atteindre le haut du flipper. 
Il semble qu'un solénoïde de 24V serait idéal. Cependant ce petit solénoïde peut être utilisé sans problème pour les slingshots qui nécessitent une force moins importante.

Remarque : d’après mes recherches, il est nécessaire d’avoir une diode branchée à chaque solénoïde car sans cela lorsque l’on envoie du courant au solénoïde puis qu’on coupe le courant pour qu’il revienne dans sa position initiale, le courant risque d’être renvoyé dans le sens inverse ce qui parasite les informations reçues par l’arduino et fait chauffer encore plus le solénoïde mais cette diode est déjà intégrée au relais.

Finalement, j’ai commencé en fin de séance à réfléchir à l’utilisation des capteurs infrarouges. Les capteurs infrarouges seront utilisés pour savoir où la balle est passée sur le pinball, en fonction de ces informations il sera alors possible de comptabiliser des points, déclencher certains moteurs ou même allumer des leds. Le câblage est tout simple, le capteur est relié au +5V et à la masse de l’arduino et il suffit ensuite de relier un dernier câble sur sur une patte digitale de l’arduino et du capteur. En effet, pour ce projet on a seulement besoin de savoir si une balle est passée ou non, donc la lecture d’un signal numérique suffit. J’ai créé ce simple programme afin de compter le nombre de passages devant un capteur :
![imageflipper](programme_infrarouge.jpg )


J’ai rapidement constaté qu’il ne sera pas possible d’utiliser la fonction de temporisation delay() dans notre algorithme sous peine de mettre tout le programme en attente. En effet, certains éléments tels que les flippers doivent pouvoir être utilisés à tout moment par le joueur et cela sans latence. Pour pallier à ce problème j’ai décidé d’utiliser la fonction millis() qui renvoie le temps écoulé en millisecondes depuis le début du programme. Ainsi j’enregistre dans une variable ce temps à chaque fois qu’un passage est détecté et je peux comparer le temps du dernier passage avec le temps actuel. Avant d’incrémenter le nombre de passages je vérifie que la dernière détection du capteur infrarouge date de plus de 100 millisecondes afin d’éviter qu’une balle ne passant pas assez pas assez rapidement devant le capteur soit comptabilisée plusieurs fois.
