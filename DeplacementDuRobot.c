#include "declaration.h"

/**
 * @file deplacement.c
 * @brief Implémente les fonctions de déplacement du robot dans l'entrepôt.
 */

/**
 * @brief Lit les commandes depuis un fichier et exécute les déplacements correspondants.
 * 
 * @param Commande_Du_Robot Chemin vers le fichier de commandes.
 * @param partie Pointeur vers la structure de la partie.
 */
void fichier_commandes(const char* Commande_Du_Robot, Partie* partie){

    FILE* fichier = fopen(Commande_Du_Robot, "r");
    if (fichier == NULL) {
        printf("Erreur à l'ouverture du fichier %s\n", Commande_Du_Robot);
        return;
    }

    char commande;
    while ((commande = fgetc(fichier)) != EOF) {
        switch (commande) {
            case 'z':
            case '^': deplacement_H(partie); break;
            case 's':
            case 'v': deplacement_B(partie); break;
            case 'q':
            case '<': deplacement_G(partie); break;
            case 'd':
            case '>': deplacement_D(partie); break;
            case ' ':
            case '\n':
            case '\r': break;
            default:
                printf("Commande inconnue : %c\n", commande);
                break;
        }
        afficher_entrepot(partie);
    }

    if (fclose(fichier) != 0) {
        printf("Erreur à la fermeture du fichier.\n");
    }
}

/**
 * @brief Permet à l'utilisateur de saisir une direction de déplacement.
 * 
 * @param partie Pointeur vers la structure de la partie.
 * @param echap Pointeur vers la touche saisie (utilisé pour quitter avec 'p').
 */
void deplacement(Partie* partie, char* echap){

    char direction;
    printf("dans quelle direction va se déplacer le robot ?");
    scanf(" %c", &direction);
    *echap = direction;

    if (*echap == 'p') return;

    switch (direction) {
        case 'd': printf("on veut déplacer le robot à droite\n"); deplacement_D(partie); break;
        case 'q': printf("on veut déplacer le robot à gauche\n"); deplacement_G(partie); break;
        case 'z': printf("on veut déplacer le robot en haut\n"); deplacement_H(partie); break;
        case 's': printf("on veut déplacer le robot en bas\n"); deplacement_B(partie); break;
        default: printf("mauvaise touche sélectionnée\n"); break;
    }
}

/**
 * @brief Déplace le robot vers la droite si le déplacement est possible.
 * 
 * @param partie Pointeur vers la structure de la partie.
 */
void deplacement_D(Partie* partie){
    Case** plateau = partie->entrepot;
    int xFrom = partie->coup.xFrom;
    int yFrom = partie->coup.yFrom;

    int comptBoite = 0;
    int i = yFrom + 1;
    while (i < NB_LIGNE && plateau[xFrom][i].e == boite) {
        comptBoite++;
        i++;
    }

    if (yFrom + comptBoite + 1 >= NB_LIGNE) {
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
void deplacement_G(Partie* partie){
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
void deplacement_B(Partie* partie){
    Case** plateau = partie->entrepot;
    int xFrom = partie->coup.xFrom;
    int yFrom = partie->coup.yFrom;

    int comptBoite = 0;
    int i = xFrom + 1;
    while (i < NB_LIGNE && plateau[i][yFrom].e == boite) {
        comptBoite++;
        i++;
    }

    if (xFrom + comptBoite + 1 >= NB_LIGNE) {
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
void deplacement_H(Partie* partie){
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

