#include "declaration.h"

/**
 * @file entrepot.c
 * @brief Fonctions nécessaires à la création, affichage et gestion de l'entrepôt.
 */

/**
 * @brief Retourne la couleur d'affichage associée à un élément.
 * 
 * @param e L'élément (mur, robot, boîte, chemin).
 * @return Un code couleur ANSI (chaîne de caractères).
 */
char* couleur_element(Element e) {
    switch (e) {
        case mur:  return "\033[30m";  // Noir
        case caseDeChemin:  return "\033[37m";  // Blanc
        case robot:  return "\033[31m";  // Rouge
        case boite: return "\033[33m";  // Marron (jaune foncé)
        default:     return "\033[0m";   // Réinitialisation
    }
}

/**
 * @brief Alloue et initialise dynamiquement l'entrepôt.
 * 
 * @param partie Pointeur vers la structure Partie.
 * @return Un tableau 2D de type Case représentant l'entrepôt.
 */
Case** creer_entrepot(Partie* partie){
    Case** entrepot = (Case**)malloc(partie->hauteur * sizeof(Case*));
    if (entrepot == NULL) {
        printf("Erreur dans l'allocation mémoire pour l'entrepôt\n");
        exit(1);
    }

    for (int i = 0; i < partie->hauteur ; i++) {
        entrepot[i] = (Case*)malloc(partie->largeur * sizeof(Case));
        if (entrepot[i] == NULL) {
            printf("Erreur dans l'allocation mémoire pour une ligne de l'entrepôt\n");
            exit(1);
        }
    }

    for (int i = 0; i < partie->hauteur; i++) {
        for (int j = 0; j < partie->largeur; j++) {
            entrepot[i][j].e = caseDeChemin;
        }
    }

    printf("petit entrepôt prédéfini\n");
    PlacementInitiale(entrepot, partie);
    
    return entrepot;
}

/**
 * @brief Place les murs, boîtes et le robot dans l'entrepôt (exemple prédéfini).
 * 
 * @param entrepot Tableau 2D représentant l'entrepôt.
 * @param partie Pointeur vers la structure Partie.
 */
void PlacementInitiale(Case** entrepot, Partie* partie){
    entrepot[2][2].e = robot;
    partie->coup.xFrom = 2;
    partie->coup.yFrom = 2;

    entrepot[1][3].e = boite;
    entrepot[1][5].e = boite;
    entrepot[2][4].e = boite;
    entrepot[3][4].e = boite;
    entrepot[4][4].e = boite;
    entrepot[5][4].e = boite;

    for (int j = 0; j < partie->largeur; j++) {
        entrepot[0][j].e = mur;
        entrepot[partie->hauteur - 1][j].e = mur;
        entrepot[j][0].e = mur;
        entrepot[j][partie->largeur - 1].e = mur;
    }

    entrepot[2][1].e = mur;
    entrepot[4][2].e = mur;
}

/**
 * @brief Libère la mémoire allouée dynamiquement pour l'entrepôt.
 * 
 * @param partie La structure Partie contenant l'entrepôt à libérer.
 */
void liberer_entrepot(Partie partie){
    Case **plateau = partie.entrepot;
    for (int i = 0; i < partie.hauteur ; i++) {
        free(plateau[i]);
    }
    free(plateau);
}

/**
 * @brief Affiche l'entrepôt dans le terminal avec couleurs et symboles.
 * 
 * @param partie Pointeur vers la structure Partie contenant l'entrepôt.
 */
void afficher_entrepot(Partie* partie){
    Case** plateau = partie->entrepot;
    for (int i = 0; i < partie->hauteur ; i++) {
        for (int j = 0; j < partie->largeur ; j++) {
            printf("%s", couleur_element(plateau[i][j].e));
            switch (plateau[i][j].e) {
                case mur:          printf("#"); break;
                case caseDeChemin: printf("."); break;
                case robot:        printf("@"); break;
                case boite:        printf("0"); break;
                case boiteG:       printf("["); break;
                case boiteD:       printf("]"); break;
                case vide:         printf("X"); break;
                default:           break;
            }
            printf("\033[0m");
        }
        printf("\n");
    }
}

