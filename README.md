# Robot-entrep

Les malheurs de l'entrepôt est un sujet proposé par Mr Saint-Bauzel.

Ce projet est constitué de différent fichier : makefile, déclaration, main, interface, déplacement du robot, commande du robot, calcul du score et SDL2.

Pour installer la bibliothèque de SDL2 (sur linux):
sudo apt-get install libsdl2-dev

Une fois l'installation de la bibliothèque il suffit de faire un make run, puis de sélectionner l'un des modes d'expériences: 

La touche o affiche l’entrepôt dans le terminal et utilise un fichier de commandes pour les déplacements. 

La touche t affiche l’entrepôt dans le terminal avec une initialisation et des déplacements définis par un fichier.

La touche u affiche l’entrepôt dans le terminal et permet de déplacer le robot avec le clavier (touches zqsd).

La touche m lance le mode élargi dans le terminal avec une initialisation et des déplacements via un fichier.

La touche l lance le mode élargi dans le terminal avec une initialisation depuis un fichier et des déplacements avec le clavier (touches zqsd).

La touche y ouvre une fenêtre graphique avec SDL2 et contrôle le robot à l’aide d’un fichier de commandes.

La touche i ouvre une fenêtre graphique avec SDL2 et permet de déplacer le robot avec le clavier (touches zqsd).

La touche p permet de quitter le programme à tout moment.
