#include "declaration.h"

/* ***************************************************

Programme qui contient les fonctions nécessaires à la création et à l'affichage de l'entrepôt

*************************************************** */


/* Fonction pour obtenir la couleur d'affichage d'un élément (Un mur sera noir ◼, une case de chemin libre sera blanc ◻, le robot sera rouge 🟥, et une boite sera marron 🟫) */

char* couleur_element(Element e) {
    switch (e) {
        case mur:  return "\033[30m";  // Noir
        case caseDeChemin:  return "\033[37m";  // Blanc
        case robot:  return "\033[31m";  // Rouge
        case boite: return "\033[33m";  // Marron (jaune foncé)
        default:     return "\033[0m";   // Réinitialisation
    }
}


/* Fonction pour allouer et initialiser l'entrepôt (du 10 par 10) */

Case** creer_entrepot(char echap, Partie* partie){
    // On alloue l'entrepôt 10 par 10
    Case** entrepot = (Case**)malloc(NB_LIGNE * sizeof(Case*));
    if (entrepot == NULL) {
        printf("Erreur dans l'allocation mémoire pour l'entrepôt\n");
        exit(1);
    }

    // On alloue chaque ligne de l'entrepôt
    for (int i = 0; i < NB_LIGNE; i++) {
        entrepot[i] = (Case*)malloc(NB_LIGNE * sizeof(Case));
        if (entrepot[i] == NULL) {
            printf("Erreur dans l'allocation mémoire pour une ligne de l'entrepôt\n");
            exit(1);
        }
    }

    // On initialise l'entrepôt avec des cases vides
    for (int i = 0; i < NB_LIGNE; i++) {
        for (int j = 0; j < NB_LIGNE; j++) {
            entrepot[i][j].e = caseDeChemin; // Par défaut, toutes les cases sont des cases de Chemin
        }
    }
    if (echap == 1){
        PlacementInitiale1(entrepot, partie);
    }else {
        PlacementInitiale2(entrepot);
    }
    return entrepot;
}

/* Fonction pour placer le robot, les murs, les boites initialement dans le cas de base*/

void PlacementInitiale1(Case** entrepot, Partie* partie){

    // On place le robot
        entrepot[3][3].e = robot;                                                                                  // C'EST ARBITRAIRE
        partie->coup.xFrom = 3;
        partie->coup.yFrom = 3;

    // On place les boites                                                                                         // C'EST ARBITRAIRE
        entrepot[4][4].e = boite;
        entrepot[8][4].e = boite;
        entrepot[8][5].e = boite;
        entrepot[8][6].e = boite;
        
    // On place les murs
    for (int j = 0; j < NB_LIGNE; j++) {
        entrepot[0][j].e = mur;
        entrepot[9][j].e = mur;
        entrepot[j][0].e = mur;
        entrepot[j][9].e = mur;
}
}

/* Fonction pour placer le robot, les murs, les boites initialement si l'entrepôt est particulier  A MODIFIER*/

void PlacementInitiale2(Case** entrepot){
    printf("Quelle taille fait l'entrepôt en longueur ?");
    printf("Quelle taille fait l'entrepôt en largeur ?");
    printf("A-ton des murs intérieurs ?");
    printf("A-ton des boites à l'intérieur de l'entrepôt ?");
    // On place le robot
        entrepot[3][3].e = robot;                                                                                  // C'EST ARBITRAIRE

    // On place les boites                                                                                         // C'EST ARBITRAIRE
        entrepot[4][3].e = boite;
        entrepot[8][4].e = boite;
        entrepot[8][5].e = boite;
        entrepot[8][6].e = boite;
        
    // On place les murs
    for (int j = 0; j < NB_LIGNE; j++) {
        entrepot[0][j].e = mur;
        entrepot[9][j].e = mur;
        entrepot[j][0].e = mur;
        entrepot[j][9].e = mur;
}
}
/* Fonction pour libérer l'espace mémoire de l'entrepôt (du 10 par 10) */

void liberer_entrepot(Partie partie){
    Case **plateau = partie.entrepot;
    for (int i = 0; i < NB_LIGNE; i++) {
            free(plateau[i]);
        }
        free(plateau);
}

/* Fonction pour afficher l'entrepôt */

void afficher_entrepot(Partie* partie){
    Case** plateau = partie->entrepot;

    // Afficher les éléments sur chaque case
    for (int i = 0; i < NB_LIGNE; i++) {
        for (int j = 0; j < NB_LIGNE; j++) {
          printf("%s", couleur_element(plateau[i][j].e));
          switch (plateau[i][j].e) {
                case mur:          printf("#"); break;
                case caseDeChemin: printf("."); break;
                case robot:        printf("@"); break;
                case boite:        printf("0"); break;
                default:           printf("E"); break;
            }
            printf("\033[0m");
        }
        printf("\n");
    }
    
}

void Initianise_entrepot(Partie* partie, char echap){
    partie->entrepot = creer_entrepot(echap, partie);

}
