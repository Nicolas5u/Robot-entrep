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
    int last_x;
    int last_y;
    int compt;
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
Case** creer_entrepot(Partie* partie);
void liberer_entrepot(Partie partie);
void afficher_entrepot(Partie* partie);
void PlacementInitiale1(Case** entrepot, Partie* partie);
void PlacementInitiale2(Case** entrepot, Partie* partie);

// Fonctions du fichier DeplacementDuRobot.c
void deplacement(Partie* partie, char* echap);
void deplacement_D(Partie* partie);
void deplacement_G(Partie* partie);
void deplacement_B(Partie* partie);
void deplacement_H(Partie* partie);

// Fonctions du fichier Calcul_Score.c
int Somme(Partie partie);

// Fonctions du fichier SDL2_pour_affichage.c
int affichage(Partie* partie);
int SDL2_fichier_commandes(const char* Commande_Du_Robot, Partie* partie);
void SDL2_Affiche_entrepot(SDL_Renderer* renderer,Partie* partie);

// Fonctions du fichier Fichier_commande
void fichier_commandes(const char* Commande_Du_Robot, Partie* partie);
void fichier_commandes_elargie(const char* Commande_Du_Robot, Partie* partie);
void determiner_dimensions(const char* commandeProf,Partie* partie);
Case** cree_et_initialisation_fichier(const char* Commande_Du_Robot, Partie* partie);
Case** cree_et_initialisation_fichier_elargie(const char* commandeProf, Partie* partie);

// Fonction du fichier deplacement_elargie.c
void deplacement_elargie(Partie* partie, char* echap);
void deplacement_H_elargie(Partie* partie);
void deplacement_D_elargie(Partie* partie);
void deplacement_G_elargie(Partie* partie);
void deplacement_vers_le_bas(Partie* partie, int x, int y);
void verif_deplacement_B_G(Partie* partie, int x,int y);
void verif_deplacement_B_D(Partie* partie, int x);

// Fonction dep_ela_test
void R_deplacement_vers_le_bas_test_recu(Partie* partie, int nb_robot);
void deplacement_vers_le_bas_test(Partie* partie);
void deplacement_vers_le_bas_test_recu(Partie* partie);


#endif
