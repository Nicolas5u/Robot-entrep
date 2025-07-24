#ifndef DECLARATION_H
#define DECLARATION_H

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#define NB_LIGNE 8


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
void fichier_commandes(const char* Commande_Du_Robot, Partie* partie);
void deplacement(Partie* partie, char* echap);
void deplacement_D(Partie* partie);
void deplacement_G(Partie* partie);
void deplacement_B(Partie* partie);
void deplacement_H(Partie* partie);

// Fonctions du fichier Calcul_Score.c
int Somme(Partie partie);

// Fonctions du fichier SDL2_pour_affichage.c
int affichage();


#endif
