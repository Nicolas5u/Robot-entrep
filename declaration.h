#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <stdlib.h>
#include <stdio.h>

#define NB_LIGNE 10

// Définition des structures
typedef enum element { 
    vide, robot, mur, boite, caseDeChemin 
} Element;

typedef struct Case {
    Element e;
} Case;

typedef struct coup {
    int xFrom;
    int yFrom;
    int xTo;
    int yTo;
} Coup;

typedef struct partie {
    Case** entrepot;
} Partie;

/* Définitions de toutes les fonctions */

// Fonctions du fichier Interface.c
char* couleur_element(Element e);
Case** creer_plateau();
void liberer_plateau(Partie partie);
void afficher_entrepot(Partie* partie);

#endif
