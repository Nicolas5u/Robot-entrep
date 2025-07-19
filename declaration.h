#ifndef DECLARATION_H
#define DECLARATION_H

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
    Coup coup;
} Partie;


/* Définitions de toutes les fonctions */

// Fonctions du fichier Interface.c
char* couleur_element(Element e);
Case** creer_entrepot(char echap, Partie* partie);
void liberer_entrepot(Partie partie);
void afficher_entrepot(Partie* partie);
void Initianise_entrepot(Partie* partie, char echap);
void PlacementInitiale1(Case** entrepot, Partie* partie);
void PlacementInitiale2(Case** entrepot, Partie* partie);

// Fonctions du fichier DeplacementDuRobot.c
void deplacement(Partie* partie, char* echap);
void deplacementD(Case** entrepot, Partie* partie);
void deplacementG(Partie* partie);
void deplacementB(Partie* partie);
void deplacementH(Partie* partie);

#endif
