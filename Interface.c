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


/* Fonction pour allouer et initialiser l'entrepôt */

Case** creer_entrepot(Partie* partie){
    // On alloue l'entrepôt
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
    
    // On initialise les positions des murs, objets et robot
    printf("petit entrepôt prédéfini\n");
    PlacementInitiale1(entrepot, partie);
    
    return entrepot;
}

/* Fonction pour placer le robot, les murs, les boites initialement dans le cas de base*/

void PlacementInitiale1(Case** entrepot, Partie* partie){

    // On place le robot
        entrepot[2][2].e = robot;                                                                                  // C'EST ARBITRAIRE
        partie->coup.xFrom = 2;
        partie->coup.yFrom = 2;

    // On place les boites                                                                                         // C'EST ARBITRAIRE
        entrepot[1][3].e = boite;
        entrepot[1][5].e = boite;
        entrepot[2][4].e = boite;
        entrepot[3][4].e = boite;
        entrepot[4][4].e = boite;
        entrepot[5][4].e = boite;
        
    // On place les murs
    for (int j = 0; j < NB_LIGNE; j++) {
        entrepot[0][j].e = mur;
        entrepot[NB_LIGNE - 1][j].e = mur;
        entrepot[j][0].e = mur;
        entrepot[j][NB_LIGNE - 1].e = mur;
    }
    entrepot[2][1].e = mur;
    entrepot[4][2].e = mur;
}

/* Fonction pour libérer l'espace mémoire de l'entrepôt */

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
