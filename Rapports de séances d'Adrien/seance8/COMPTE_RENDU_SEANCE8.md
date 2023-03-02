**Avant la séance :**

Lors de la séance précédente nous avions préparé nos planches finales et toutes les bordures du flipper. Nous avons profité des vacances pour nous rendre au Fablab afin d’assembler notre flipper, pour cela nous avons commencé par coller les 3 fines planches et visser les bordures sur les côtés.

<img src="planche_flipper.jpg" width="300">

Nous avons ainsi fabriqué la zone de lancement : 

DETAILS !!!

<img src="lanceur.jpg" width="300">
https://youtu.be/IZiwfpQI0ls

Préalablement, j’avais imprimé en 3D toutes les pièces modélisées, testées et ajustées lors des séances précédentes afin d’en avoir bon nombre. J’ai notamment dû modifier l’épaisseur de la surface supérieure des tendeurs à élastiques des slingshots car la pièce se courbait en raison de la force de tension exercée par l’élastique sur la pièce. 
Il a fallu limer certaines pièces afin de s’assurer que la mécanique des pièces en mouvement (bumpers, flippers et slingshots) s’effectue sans trop de frottements. J’ai également taraudé de nombreuses pièces pour pouvoir les fixer directement en vissant dans du plastique. 

Il a fallu plusieurs heures pour régler les flippers avec la bonne inclinaison sans bloquer le mouvement des solénoïdes qui les contrôlent. En effet, ceux-ci doivent être parfaitement disposés pour que le mouvement de rotation puisse s’effectuer correctement. Pour cela j’ai imprimé une pièce donnant l’inclinaison utilisée dans la plupart des pinball. Après de nombreux réglages il y avait encore des blocages dans le mécanisme, j’ai donc dû limer les pièces plastiques afin de rajouter du jeu pour que les mouvements soient moins contraints.

Ensuite j’ai fixé les capteurs infrarouges sous la planche. Pour les positionner de façon à ce que les leds émettrices et réceptrices soient très proche de la plaque de plexiglass afin que lorsque la bille roule sur celle-ci, elle soit détectée, j’ai modélisé un support à la bonne hauteur sur lequel j’ai ajouté 3 trous pour que les résistances et les leds du circuit intégré du capteur s’emboîtent à l’intérieur sans être endommagées. Voici la pièce modélisée : 

<img src="modelisation_supportIR.jpg" width="300"><img src="capteurIR+support.jpg" width="250">
<img src="fixation_supportIR.jpg" width="200">


Précédemment j’avais également fabriqué par découpe et gravure laser un élément propre à notre flipper : la “roue de la fortune.”  Cet élément du jeu permet de gagner un bonus au hasard indiqué par les la led associée à la case en question. J’ai du alors découper un ruban de néo pixels afin de les disposer de façon circulaire dans les trous prévus et ensuite ressouder tous les néo pixels entre eux afin de pouvoir toujours les alimenter et contrôler avec seulement 3 fils.

<img src="rouefortune_cablage.jpg" width="300">

Une autre étape très délicate dans l’assemblage de nos pièces est la fixation des microswitch permettant de détecter un impact sur l’élastique des slingshot. En effet, cela nécessite une très grande sensibilité. Tout d’abord j’ai testé plusieurs microswitch différents afin de choisir les plus sensibles possibles, une fois ce choix effectué, étant donné que sur un même composant il y a des différences de fabrication j’en ai testé une vingtaine afin de sélectionner ceux qui se déclenchent avec le moins de force possible. 
Ensuite il a fallu les placer sous les slingshots. Comme expliqué dans les premiers comptes-rendus lors de la réalisation d’un prototype, ils doivent être positionnés de façon à ce que la lamelle subisse une pression initiale exercée par l’élastique afin qu’ils se déclenchent au moindre contact mais en faisant attention à ce que celui-ci ne reste pas bloqué en position enfoncée. La pièce du slingshot ne permettant pas de régler facilement la position de ceux-ci, j’ai décidé de créer une copie de celle-ci en ajoutant un trou à l’intérieur afin de pouvoir y passer des doigts pour placer l’interrupteur. Cette pièce étant utilisée uniquement le temps de déterminer l’emplacement des interrupteurs.

<img src="modelisation_slingshot_positionnement.jpg" width="300">

Pour les fixer j’ai modélisé et imprimé 4 supports permettant de les surélever à la bonne hauteur. Une fois la position optimale déterminée j’ai tracé le contour de ceux-ci sur la planche au crayon pour perçer des trous permettant de les visser.

<img src="trous_slingshot.jpg" width="300">
<img src="slingshot_placement_microswitch_1.jpg" width="300">
<img src="slingshot_placement_microswitch_2.jpg" width="300">

Durant le temps restant avant la séance j’ai réfléchis au cablâge des composants électroniques en continuant et en adaptant le schéma électronique commencé à la séance précédente sur le logiciel Fritzing. J’ai ensuite fixé les différents composants sous la planche et j’ai câblé le convertisseur entre le connecteur d’alimentation et l’arduino (après l’avoir réglé avec un multimètre pour qu’il transforme la tension de 24V en une tension de 5V en sortie).

Adapter pièce zone de lancement

Finalement j’ai modélisé en 3D l'entrée de la rampe. J’ai effectué différents tests pour déterminer l’inclinaison de celle-ci afin que la bille ait assez de vitesse pour monter en haut de celle- ci. J’ai également dû effectuer un arrondi adapté en haut de la rampe pour éviter que celle-ci ne revienne en arrière. Étant donné que le capteur infrarouge permettant de comptabiliser un passage dans la rampe dans le score est devant l’entrée de la rampe, il risque d’être déclenché lors d’un simple passage à proximité de celle-ci. J’ai donc ajouté à la rampe 2 barrières d’une longueur de 20 mm afin d’éviter de comptabiliser par erreur un passage dans la rampe. 
De plus si la bille repasse devant le capteur infrarouge un très bref instant après le premier passage, cela signifie que le joueur n’a pas réussi à l’envoyer en haut de la rampe et donc on n’ajoutera pas de points.

<img src="modelisation_rampe.jpg" width="300">
<img src="entreerampe.jpg" width="300">

Voici l’avancée du pinball avant la séance : 

<img src="flipper_vuedehaut.jpg" width="300">

Remarque : un slingshot à été dévissé sur la photo car nous sommes en train de souder les fils sur les microswitch.

**Pendant la séance :**

Étant donné le peu de temps restant avant la date de présentation finale du projet, puisque tous les composants principaux maintenant fixés fonctionnent correctement mécaniquement, nous avons décidé de se consacrer pleinement en équipe au câblage des composants sous la planche afin d’être sûr de pouvoir présenter une version fonctionnelle. Pour cela nous avons commencé par câbler tous les solénoïdes en parallèle afin d’avoir la même tension pour chaque solénoïde. 
Pour relier toutes les masses entre elles nous avons utilisé 2 connecteurs wago à leviers. Un pour le haut du flipper et un pour le bas du flipper ,les deux étant reliés par un câble afin d’avoir une masse commune. 

<img src="connecteurWago.jpg" width="300">

Cela permet d’éviter de perdre du temps à effectuer des soudures et de pouvoir facilement débrancher un fil en cas de problème.

Puis nous avons écrit un petit programme activant 3 solénoïdes en simultané afin de vérifier que tout fonctionne correctement. 
Puis j’ai écrit un autre code pour activer un solénoïde un par un toutes les secondes pour vérifier qu’ils fonctionnent tous. 
Nous nous sommes alors aperçu que 2 solénoïdes ne fonctionnaient pas. Ceux-ci étaient câblés dans le mauvais sens. Le constructeur n’a pas mis de code couleur permettant de différencier les 2 fils du solénoïde et pourtant inverser les 2 fils inverse également le sens du champ magnétique et donc le piston du solénoïde ne peut pas se déplacer dans la bonne direction.
Finalement j’ai commencé à ajouter des “serres câbles” afin d’avoir un câblage plus ordonné et donc de pouvoir nous y retrouver plus facilement.

Voici le dessous de la planche avec le câblage en cours d’installation (il reste encore du travail en cable management pour que tout soit propre à la fin).

<img src="flipper_cablage_dessous.jpg" width="300">


**Étapes finales à réaliser :**

- Il nous reste désormais à terminer le câblage en branchant nos 8 capteurs infrarouges, les 2 boutons des flippers, les 4 microswitch des slingshots + 3 pour les cibles, l’écran, la roue de la fortune et un ruban neopixel de décoration. 

- Coller les cibles sur les microswitch et les assembler sur le support puis les fixer sur la planche.

- Modifier l’inclinaison de la bordure inférieure ramenant la bille en zone de lancement.

- Fixer l’écran et la roue de la fortune sur le flipper

- Finaliser la partie programmation, nous avions déjà réalisé des programmes pour tester chaque composant indépendamment, il faut désormais réaliser le programme complet permettant d’automatiser le fonctionnement d’une partie.

- Finir la fabrication de la rampe et la placer sur le flipper.

- Finitions et correction d’éventuels bugs
