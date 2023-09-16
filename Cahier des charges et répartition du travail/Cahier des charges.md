# Cahier des charges du projet Flipper #

Notre objectif est de fabriquer un Flipper (Pinball en anglais) à l’aide d’une carte Arduino, de moteurs et de capteurs en moins de 3 mois.

Le principe de ce jeu est de marquer le plus de points possible en dirigeant une ou plusieurs billes métalliques sur un plateau vers des cibles interactives. Nous souhaitons intégrer les principaux composants d’un Flipper dans une version moins encombrante avec des composants abordables afin de rendre ce jeu accessible au plus grand nombre dans un projet open source. Ceci nous permettra de renforcer nos connaissances par la pratique, en apprenant à utiliser une grande variété d'outils et de composants, mais aussi d'acquérir des compétences en gestion de projets.

Les principales parties de notre Flipper seront :

* Une planche de bois.
* Les Flippers (petits leviers contrôlés par le joueur, qui permettent d'envoyer la bille sur les différents éléments du jeu).
* Boutons (permettent de contrôler les flippers).
* Bumpers (renvoient la balle dans la direction opposée et ajoutent des points au joueur).
* Slingshots (font rebondir la bille sur des élastiques munis de leviers mécaniques pour la repositionner dans la zone de jeu).
* Tige avec ressort munie d'une poignée (permettant de lancer la bille).
* Capteurs de passages (capteurs infrarouges permettant de savoir où la bille est passée afin d’ajouter des points ou de déclencher certains éléments de jeu).
* Des cibles (surfaces munies de "microswitches" permettant de détecter un contact afin de comptabiliser des points).
* Rampes que la bille peut emprunter pour marquer des points.
* Afficheur LCD (affiche le score, le nombre d'essais restants et des messages relatifs à la partie).
* Mode MultiBille (bonus relâchant plusieurs billes simultanément depuis la partie haute du flipper).
* Leds (décoration et interactivité du flipper, s’allument quand certains capteurs sont déclenchés).

Bonus s'il reste du temps : Une roue de la fortune déclenchée à certains moments de la partie (roue tournante permettant de gagner des points en fonction de la position d’arrêt de la roue).
