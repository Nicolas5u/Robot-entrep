#include "declaration.h"

/**
 * @brief Déplace le robot vers la droite si le déplacement est possible.
 * 
 * @param partie Pointeur vers la structure de la partie.
 */
void deplacement_D_élargie(Partie* partie, int tailleL){
    Case** plateau = partie->entrepot;
    int xFrom = partie->coup.xFrom;
    int yFrom = partie->coup.yFrom;

    int comptBoite = 0;
    int i = yFrom + 1;
    while (i < tailleL && plateau[xFrom][i].e == boite) {
        comptBoite++;
        i++;
    }

    if (yFrom + comptBoite + 1 >= tailleL) {
        printf("Déplacement impossible, limite de l'entrepôt\n");
        return;
    }

    if (plateau[xFrom][yFrom + comptBoite + 1].e == caseDeChemin){
        plateau[xFrom][yFrom + comptBoite + 1].e = boite;
        plateau[xFrom][yFrom + 1].e = robot;
        plateau[xFrom][yFrom].e = caseDeChemin;
        partie->coup.yFrom = yFrom + 1;
    } else {
        printf("Déplacement impossible, le robot est bloqué\n");
    }
}

/**
 * @brief Déplace le robot vers la gauche si le déplacement est possible.
 * 
 * @param partie Pointeur vers la structure de la partie.
 */
void deplacement_G_élargie(Partie* partie){
    Case** plateau = partie->entrepot;
    int xFrom = partie->coup.xFrom;
    int yFrom = partie->coup.yFrom;

    int comptBoite = 0;
    int i = yFrom - 1;
    while (i >= 0 && plateau[xFrom][i].e == boite) {
        comptBoite++;
        i--;
    }

    if (yFrom - comptBoite - 1 < 0) {
        printf("Déplacement impossible, limite de l'entrepôt\n");
        return;
    }

    if (plateau[xFrom][yFrom - comptBoite - 1].e == caseDeChemin){
        plateau[xFrom][yFrom - comptBoite - 1].e = boite;
        plateau[xFrom][yFrom - 1].e = robot;
        plateau[xFrom][yFrom].e = caseDeChemin;
        partie->coup.yFrom = yFrom - 1;
    } else {
        printf("Déplacement impossible, le robot est bloqué\n");
    }
}

/**
 * @brief Déplace le robot vers le bas si le déplacement est possible.
 * 
 * @param partie Pointeur vers la structure de la partie.
 */
void deplacement_B_élargie(Partie* partie, int tailleC){
    Case** plateau = partie->entrepot;
    int xFrom = partie->coup.xFrom;
    int yFrom = partie->coup.yFrom;

    int comptBoite = 0;
    int i = xFrom + 1;
    while (i < tailleC && plateau[i][yFrom].e == boite) {
        comptBoite++;
        i++;
    }

    if (xFrom + comptBoite + 1 >= tailleC) {
        printf("Déplacement impossible, limite de l'entrepôt\n");
        return;
    }

    if (plateau[xFrom + comptBoite + 1][yFrom].e == caseDeChemin){
        plateau[xFrom + comptBoite + 1][yFrom].e = boite;
        plateau[xFrom + 1][yFrom].e = robot;
        plateau[xFrom][yFrom].e = caseDeChemin;
        partie->coup.xFrom = xFrom + 1;
    } else {
        printf("Déplacement impossible, le robot est bloqué\n");
    }
}

/**
 * @brief Déplace le robot vers le haut si le déplacement est possible.
 * 
 * @param partie Pointeur vers la structure de la partie.
 */
void deplacement_H_élargie(Partie* partie){
    Case** plateau = partie->entrepot;
    int xFrom = partie->coup.xFrom;
    int yFrom = partie->coup.yFrom;

    int comptBoite = 0;
    int i = xFrom - 1;
    while (i >= 0 && plateau[i][yFrom].e == boite) {
        comptBoite++;
        i--;
    }

    if (xFrom - comptBoite - 1 < 0) {
        printf("Déplacement impossible, limite de l'entrepôt\n");
        return;
    }

    if (plateau[xFrom - comptBoite - 1][yFrom].e == caseDeChemin){
        plateau[xFrom - comptBoite - 1][yFrom].e = boite;
        plateau[xFrom - 1][yFrom].e = robot;
        plateau[xFrom][yFrom].e = caseDeChemin;
        partie->coup.xFrom = xFrom - 1;
    } else {
        printf("Déplacement impossible, le robot est bloqué\n");
    }
    
}
