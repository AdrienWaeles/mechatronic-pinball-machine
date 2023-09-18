**Avant la séance :**


Pour commencer j’ai fixé un des 2 micro-interrupteurs du slingshot (pièce constituée d’un élastique destinée à renvoyer la bille dans la direction opposée, voir compte rendus précédents) sur la planche du prototype réalisé lors des séances précédentes. 

<img src="Images des rapports/Images séance 4/slingshot_fixation_microInterrupteur.jpg" width="300">

Cela a nécessité beaucoup de minutie car si la lamelle du micro-interrupteur n’est pas assez tendue par l’élastique, l’impact de la bille ne le déclenche pas (à moins de l’envoyer avec une très grande vitesse). 
Et si elle est trop tendue, la lamelle ne revient plus à sa position initiale après l’impact en raison de la pression exercée par l’élastique (le bouton de l’interrupteur est alors constamment enfoncé). 


Il a fallu surélever légèrement le micro-interrupteur de la planche pour que la bille frappe celui-ci à hauteur de son centre de gravité afin qu’elle exerce une force maximale sur la lamelle. Provisoirement cela a été fait avec 2 petits écrous. Sur la version finale il pourra être utile de fabriquer une petite pièce adaptée. Sur le slingshot final il y aura un micro-interrupteur de chaque côté de l’élastique afin d’avoir la même sensibilité de détection d'impact des deux côtés. 


Après de nombreux tests pour fixer le micro-interrupteur de manière optimale voici le résultat : https://youtube.com/shorts/6lyibMg2PRw


J’ai ensuite réalisé un prototype d’un bumper à l’aide d’un solénoide (KK-0630B, 24V, 600mA, 10mm de course, 8Newtons) sur la planche de prototypage que j’avais utilisé pour créer le slingshot. Pour cela je me suis aidé de ce design : https://www.thingiverse.com/thing:3286052. Le bumper est constitué de deux pièces, le cône qui s’abaisse sur la balle et une pièce fixe qui permet de maintenir le cône droit, dans lequel la première pièce va coulisser.

<img src="Images des rapports/Images séance 4/bumper_prototype.jpg" width="300">

J’ai importé ces pièces dans un logiciel de modélisation 3D, et j’ai modifié l’écartement entre les 2 pattes qui viennent se serrer sur le solénoïde pour pouvoir y fixer le nôtre, qui est bien plus petit que celui utilisé par le créateur des fichiers 3D.

<img src="Images des rapports/Images séance 4/bumper_cone_modelisation3d.jpg" width="300">

Le fonctionnement est le même que celui expliqué dans le compte rendu de la séance 3 : la pièce conique qui est attachée au solénoïde va s'abaisser sur la balle pour la pousser dans la direction opposée. Pour fixer le bumper à la planche, j’ai percé un trou dans le prototype et à partir des dimensions mesurées, j’ai modélisé et imprimé une équerre qui permet de fixer le solénoïde sous la planche. 

<img src="Images des rapports/Images séance 4/équerre_solenoide.jpg" width="300">

Remarque : l’équerre sera modifiée par la suite étant donné en raison d’une erreur d’orientation de la pièce lors de la modélisation.

Voici la démonstration en vidéo : https://youtube.com/shorts/1k2h37szUpM

**Durant la séance :**
Après avoir présenté l’avancée de notre projet lors d’un oral de 10 minutes. Nous avons commencé à réaliser le système permettant de détecter le contact de la bille sur le bumper. Pour cela, nous avons coupé une fine plaque de métal au Fablab aux dimensions du bumper qui sera encastrée dans la planche juste en dessous de celui-ci. Nous avons trouvé un fil rigide que nous allons insérer dans une rainure sur l’extrémité haute de la pièce du bumper. Ainsi quand la bille roulera sur la plaque métallique et qu’elle sera en contact en même temps avec le fil, le bumper sera déclenché et l’arduino recevra un signal permettant d’ajouter des points au joueur.


J’ai pu remarquer que le mouvement vertical de la pièce conique du bumper imprimée en 3d est interrompu par la planche. Donc on ne profite pas de l'entièreté de la course qu'offre le piston du solénoide. Et cela puisque les pattes de la pièce conique ne sont pas assez longues. J’ai alors modifié la modélisation 3d pour prolonger celles-ci afin que le bumper puisse avoir une position initiale plus haute et donc pour que le solénoïde puisse effectuer sa course entièrement.
J’en ai profité pour ajouter la rainure qui permettra d’y insérer le bout de métal. 

Finalement, je me suis intéressé au fonctionnement d’un écran lcd qui permettra d’afficher le score du joueur tout au long de la partie et éventuellement des messages relatifs au déroulement de la partie. L’écran lcd utilisé est “QAPASS 1602A”. Étant donné que nous avons besoin de garder un grand nombre de broches libres pour les nombreux composants de notre flipper, afin de réduire le nombre de connexions que nécessite un afficheur LCD, nous utilisons une interface série I2C (modèle HW-061) qui fait le lien entre l’arduino et l’afficheur. 

<img src="Images des rapports/Images séance 4/i2c-module_documentation.jpg " width="300">

Afin de connecter cette interface à l’écran, j’y ai soudé une bande de broches dans laquelle j’ai inséré les 16 connecteurs de l’interface. Le programme pour faire fonctionner l’écran et y afficher le nombre de points sera réalisé avant la prochaine séance.

<img src="Images des rapports/Images séance 4/module_i2c+lcd_branchement.jpeg " width="300">
