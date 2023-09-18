**Avant la séance :**

À partir de la liste de composants établie au début du projet dans le cahier des charges, nous avons cherché les références des composants à acheter pour le pinball, notamment en faisant des recherches sur la force en newton et le voltage nécessaire pour exercer suffisamment de force sur la balle (voir liste des composants). Puis nous nous sommes rendus dans plusieurs magasins de bricolage afin de trouver des ressorts et élastiques, pour pouvoir avancer le projet. Le ressort permettra de fabriquer le lanceur manuel de bille.

Après avoir reçu des élastiques et des billes adaptés au projet, j’ai créé un prototype d’un slingshot en perçant une planche et en y fixant des clous. Cette pièce située au-dessus des flippers permet de faire rebondir la balle sur un élastique lorsque celui-ci est touché afin de ramener la bille dans la zone de jeu. Elle est constituée d’un élastique tendu auquel sont collés des micro-interrupteurs et sous la planche se trouve un solénoïde. La référence du solénoïde actuellement utilisé est : JF-0730B (12V, 5N, 10mm de course).

<img src="Images des rapports/Images séance 2/prototype_slingshot.jpg" width="500">

Le fonctionnement est le suivant, lorsque la bille vient taper l’élastique celui-ci exerce une pression qui va déclencher au moins un des 2 interrupteurs disposés de chaque côté de l’élastique, une fois le signal reçu on enclenche immédiatement le solénoïde pour tendre l’élastique dans l’autre sens avec une petite pièce en plastique passant à travers la planche afin de repousser la balle. Voici la pièce en question modélisé en 3d :

<img src="Images des rapports/Images séance 2/bras_slingshot.jpg" width="300">

J’ai testé différents micro-interrupteurs afin de choisir les plus sensibles pour que le slingshot se déclenche même si la balle arrive dessus avec une faible vitesse. Pour avoir une meilleure sensibilité, une astuce consiste à placer le bouton de façon à tendre légèrement l’élastique avec celui-ci sans que cela enclenche l'interrupteur. Finalement j’ai modélisé et imprimé une équerre permettant de fixer le solénoïde en dessous de la planche.

Pour la création des cibles du pinball, nous avons modélisé sur Fusion 360 un support permettant d’y loger 3 micro-interrupteurs et 3 leds associées à chaque interrupteur qui s’allumeront lorsque leur interrupteur associé est touché. 3 trous en haut de l'objet permettent d'y insérer des leds, en dessous de la pièce, des trous permettent de passer les câbles de chaque led et interrupteur et 2 autres permettent de fixer le support à la planche.


<img src="Images des rapports/Images séance 2/support_cibles_vue3d.jpg" width="300">
<img src="Images des rapports/Images séance 2/support_cibles_vue3ddessous.jpg" width="300">

Finalement j’ai modélisé en 3d une poignée sur Blender. Cette poignée servira à créer le lanceur manuel de bille. Le lanceur sera constitué d'une tige en bois associée à un ressort avec d'un côté la poignée sur laquelle on va tirer pour propulser la balle en haut du pinball. 

<img src="Images des rapports/Images séance 2/poignee_blender_vue3d.jpg" width="300">
<img src="Images des rapports/Images séance 2/poignee_blender_vuedecote.jpg" width="300">


**Durant la séance :**

Dans un premier temps, j’ai adapté le code réalisé lors de la première séance qui servait à déclencher les solénoïdes des flippers avec boutons. Le fonctionnement des slingshots est en effet très similaire, la seule différence entre les 2 programmes est que pour les slingshots après le déclenchement du solénoïde celui-ci doit se rétracter immédiatement même si l’interrupteur reste enfoncé pendant plusieurs millisecondes. Ainsi dans le programme, le solénoide est déclenché seulement lorsque la valeur renvoyée par l'interrupteur passe de l'état HIGH à LOW (mais pas l'inverse car le solénoide ne doit pas se réenclencher lorsque l'interrupteur est relaché). (le code commenté est disponible sur le github). 

Puis nous avons fixé le solénoïde en dessous de la planche du prototype à l’aide de petites vis et de l’équerre préalablement imprimée en 3d (le solénoide sera mieux fixé à la planche par la suite, ceci reste un prototype). 

<img src="Images des rapports/Images séance 2/equerre_fixation_solenoide.jpg" width="300">

Le bras du solénoïde doit être placé un peu en retrait de l'élastique afin d’éviter que la bille ne frappe la pièce en plastique au lieu de l’élastique ce qui ne déclencherait pas les micro-interrupteurs mais tout en restant le plus proche de celui-ci pour que le mouvement du solénoïde tende l'élastique au maximum.

Il a fallu ainsi réaliser de nombreux tests pour trouver le positionnement optimal du bras du solénoïde et des micro-interrupteurs et la tension de l'élastique à appliquer pour que la balle déclenche correctement l'interrupteur (il y en aura 2 sur la version finale) et que le solénoide tende suffisamment l'élastique. Le prototype nous permet ainsi de vérifier que tout fonctionne et de déterminer le placement de chaque élément du slingshot afin de fabriquer plus tard une pièce avec les bonnes mesures. Voici une démonstration du prototype avec une bille : https://youtu.be/Ld9HjYVpliU

Comme on peut le voir lorsque que le micro-interrupteur est bien placé, le choc de la bille sur l’élastique déclenche bien le slingshot et cela même si la bille arrive avec une vitesse peu élevée sur le slingshot. Le prototype semble donc fonctionner cependant le slingshot ne renvoie pas la balle avec beaucoup de force et cela en raison notamment de la course du solénoïde de seulement 10mm qui ne tend pas suffisamment l’élastique. Pour améliorer cela on pourra éventuellement par la suite tester avec un autre solénoïde (ayant une course plus grande ou plus de force pour tendre l'élastique plus efficacement) ou changer la pièce par un système de levier.

En fin de séance, j'ai réfléchis à la meilleure manière de fixer les micro-interrupteurs et recherché des vis adaptées afin de pouvoir finaliser le prototype du slingshot. Puis nous avons commencé à imaginer la conception du lanceur de billes en cherchant une tige en bois adaptée aux ressorts que nous avions trouvé.

