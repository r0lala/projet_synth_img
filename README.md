# Light Corridor

## Notre Projet

Light Corridor est un jeu dans lequel le joueur possède une raquette avec laquelle il doit renvoyer une 

## Fonctionnalités

blablabla

## Difficultés

Matériel : 
- Quelques difficultés à utiliser GitHub et mettre en place les fichiers sur le repo. En effet, comme expliqué plus bas, nous ne travaillions pas sur les mêmes installations/configurations, il était donc compliqué de partager un repo Git sans mettre en péril ce que nous avions déjà codé.

- Nous ne travaillons pas avec les mêmes installations et à cause de soucis avec GitHub, nous avons mis du temps avant de pouvoir rejoindre les codes que nous avions fait séparément. De plus, nous n'avions pas nécessairement utilisé les mêmes paramètres (axe x,y,z // placement de la caméra // ...). De ce fait, certaines parties du code faites par l'une n'ont finalement pas pu être utilisées.

- Malgré de nombreuses tentatives avec différentes installation, OpenGL ne fonctionne toujours pas sur l'ordinateur de Romane, elle a été obligé de travailler sur les machines de l'université. Malheureusement, à cause des cours, partiels, autres projets, etc. Elle n'a pas toujours pu se rendre sur place pour travailler sur ce projet.

Code :
- Pour les obstacles, nous avions essayé de faire une fonction qui afficherait un obstable au hasard parmi les obstacles créés. Néanmoins, comme la fenêtre reload à chaque passage de boucle, cela relançait la fonction aléatoire ce qui faisait apparaître les obstables de façon sporadique très rapide. Il aurait fallut stocker l'obstacle obtenu dans une variable mais nous ne savions pas comment réutiliser cette variable pour garder l'obstacle.

- Lorsque l'utilisateur agrandit la fenêtre de jeu, la raquette n'est plus tout à fait au même endroit que la souris de l'utiisateur. Elle continue de suivre la trajectoire du curseur mais il y a un décalage entre les deux.

- Pour la création du menu, nous ne savions pas trop comment nous y prendre. Lilou avait commencé à faire quelques essais en essayant de récupérer la position de la souris au moment du clic pour déterminer si la personne veut "Jouer" ou "Quitter" ; mais finalement, nous avons pnesé qu'il serait plus simple d'afficher une image avec des instructions et en fonction de définir une action pour un bouton (J pour Jouer, ESCAPE pour quitter). Néanmoins, nous avons eu des soucis avec l'utilisation de stbi_load.


## Spéciale dédicace

Merci à Enguerrand pour le template.
