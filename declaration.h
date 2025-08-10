#ifndef DECLARATION_H
#define DECLARATION_H

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>


// Définition des structures
typedef enum { 
    vide, robot, mur, boite, caseDeChemin, boiteG, boiteD 
} Element;

typedef struct {
    Element e;
} Case;

typedef struct {
    int xFrom;
    int yFrom;
} Coup;

typedef struct {
    Case** entrepot;
    Coup coup;
    int largeur;
    int hauteur;
} Partie;


/* Définitions de toutes les fonctions */

// Fonctions du fichier Interface.c
char* couleur_element(Element e);
Case** creer_entrepot(Partie* partie,int tailleC,int tailleL);
void liberer_entrepot(Partie partie,int tailleL);
void afficher_entrepot(Partie* partie);
void PlacementInitiale1(Case** entrepot, Partie* partie,int tailleC,int tailleL);
void PlacementInitiale2(Case** entrepot, Partie* partie);

// Fonctions du fichier DeplacementDuRobot.c
void deplacement(Partie* partie, char* echap, int tailleL, int tailleC);
void deplacement_D(Partie* partie, int tailleL);
void deplacement_G(Partie* partie);
void deplacement_B(Partie* partie, int tailleC);
void deplacement_H(Partie* partie);

// Fonctions du fichier Calcul_Score.c
int Somme(Partie partie);

// Fonctions du fichier SDL2_pour_affichage.c
int affichage(Partie* partie, int tailleL, int tailleC);
int SDL2_fichier_commandes(const char* Commande_Du_Robot, Partie* partie, int tailleL, int tailleC);
void SDL2_Affiche_entrepot(SDL_Renderer* renderer,Partie* partie, int tailleL, int tailleC);

// Fonctions du fichier Fichier_commande
void fichier_commandes(const char* Commande_Du_Robot, Partie* partie, int tailleL, int tailleC);
void determiner_dimensions(const char* commandeProf,Partie* partie);
Case** cree_et_initialisation_fichier(const char* Commande_Du_Robot, Partie* partie);

// Fonctions du fichier etrep_elargie
void fichier_commandes_elargie(const char* Commande_Du_Robot, Partie* partie, int tailleL, int tailleC);
Case** cree_et_initialisation_fichier_elargie(const char* commandeProf, Partie* partie);
void determiner_dimensions_elargie(const char* commandeProf,Partie* partie);

// deplacement élargie
void deplacement_D_elargie(Partie* partie, int tailleL);
void deplacement_G_elargie(Partie* partie);
void deplacement_B_elargie(Partie* partie, int tailleC);
void deplacement_H_elargie(Partie* partie);


#endif
