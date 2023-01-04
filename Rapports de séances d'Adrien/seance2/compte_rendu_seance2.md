**Avant la séance :**

À partir de la liste de composants établie au début du projet dans le cahier des charges, nous avons cherché les références des composants à acheter pour le pinball (notamment en faisant des recherches sur la force en newton et le voltage nécessaire pour appliquer assez de force sur la balle) et nous sommes rendus dans plusieurs magasins de bricolage afin de trouver des ressorts, élastiques, pour éviter des délais de réception trop long via internet.

Après avoir reçu des élastiques et des billes adaptés au projet, j’ai créé un prototype d’un slingshot en perçant une planche et en y fixant des clous. Cette pièce située au-dessus des flippers permet de faire rebondir la balle sur un élastique lorsque celui-ci est touché afin de ramener la bille dans la zone de jeu. 
Elle est constituée d’un élastique tendu auquel sont collés des micro interrupteurs et sous la planche se trouve un solénoïde. 
Le fonctionnement est le suivant, lorsque la bille vient tapper l’élastique celui ci exerce une pression qui va déclencher au moins un des 2 interrupteurs disposés de chaque côté de l’élastique, une fois le signal reçu on enclenche immédiatement le solénoïde pour tendre l’élastique dans l’autre sens avec un petite pièce en plastique passant à travers la planche afin de repousser la balle. Voici le levier en question modélisé en 3d :

J’ai essayé différents micro interrupteurs afin de choisir les plus sensibles pour que le slingshot se déclenche même si la balle arrive dessus avec une faible vitesse. Pour avoir une bonne sensibilité il faut placer le bouton de façon à tendre légèrement l’élastique avec celui-ci. Finalement j’ai modélisé et imprimé une équerre permettant de fixer le solénoïde en dessous de la planche.

Pour la création des cibles du pinball, nous avons modélisé sur Fusion 360 un support permettant d’y loger 3 micro-interrupteurs et 3 leds associées à chaque interrupteurs qui s’allumeront si un interrupteur est touché puis je l’ai imprimé en 3D.

Finalement j’ai modélisé une poignée sur Blender. Cette poignée servira à créer le lanceur  manuel de balles constitué de celle-ci, d’un ressort et d’une tige.

![imagepoignee](poignee_blender_vue3d.jpg)
![imagepoignee](poignee_blender_vuedecote.jpg)



**Durant la séance :**

Dans un premier temps, j’ai adapté le code réalisé lors de la première séance qui servait à déclencher les solénoïdes des flippers lorsque l’on appuyait sur les boutons. Le fonctionnement des slingshots et très similaires, la seule différence entre les 2 programmes est que pour les slingshots après le déclenchement du solénoïde celui-ci doit se rétracter immédiatement même si l’interrupteur reste enfoncé pendant plusieurs millisecondes (le code est disponible sur le github). 
Puis nous avons fixé le solénoïde en dessous de la planche du prototype à l’aide de petites vis et de l’équerre préalablement imprimée en 3d. Le levier du solénoïde doit être placé un peu en retrait de l'élastique afin d’éviter que la bille ne frappe la pièce en plastique au lieu de l’élastique ce qui ne déclencherait pas les micro-interrupteurs.
Finalement nous avons pu effectuer des tests sur le prototype avec une bille : https://youtu.be/Ld9HjYVpliU
Comme on peut le voir lorsque que le micro-interrupteur est bien placé, le choc de la bille sur l’élastique déclenche bien le slingshot et cela même de manière assez sensible. Le prototype semble donc fonctionner cependant le slingshot ne renvoie pas la balle très fort et cela en raison notamment de la course du solénoïde de seulement 10mm qui ne tend pas suffisamment l’élastique. Pour améliorer cela on pourra éventuellement par la suite tester avec un autre solénoïde ou changer la pièce par un système de levier.

