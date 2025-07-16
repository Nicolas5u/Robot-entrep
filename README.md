# Robot-entrep
Les malheurs de l'entrepôt est un sujet proposé par Mr Saint-Bauzel 
Ce projet possède un makefile, il suffit donc d'écrire "make" dans un terminal pour compiler le projet. Ensuite, en appelant le main nous avons un premier choix qui nous est proposé, soit d'utilisé l'entrepôt prédéfinit en tapant 1 soit d'en créer un soit même en tapant autre chose. Pour sortir du programme il suffit d'envoyer p à n'importe quel moment.
Le projet est composé de plusieurs fichier dont Interface qui permet de gérer l'affichage de l'entrepôt.
Nous avons également le fichier DeplacementDuRobot.c qui s'occupe des déplacements du robot.

Dans le fichier interface nous avons les fonctions suivantes: 

/* Fonction pour obtenir la couleur d'affichage d'un élément (Un mur sera noir ◼, une case de chemin libre sera blanc ◻, le robot sera rouge 🟥, et une boite sera marron 🟫) */

/* Fonction pour allouer et initialiser l'entrepôt (du 10 par 10) */

/* Fonction pour libérer l'espace mémoire de l'entrepôt (du 10 par 10) */
