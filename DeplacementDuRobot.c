#include "declaration.h"

/* ***************************************************

Programme qui contient les fonctions nécessaires aux déplacements du robots

*************************************************** */


void fichier_commandes(const char* Commande_Du_Robot, Partie* partie){

    FILE* fichier = fopen(Commande_Du_Robot, "r"); // pas besoin de déclarer la structure et ouvre le fichier en lecture
    if (fichier == NULL) {
        printf("Erreur à l'ouverture du fichier %s\n", Commande_Du_Robot);
        return;
    }

    char commande;
    while ((commande = fgetc(fichier)) != EOF) { // mise à jour de la commande à chaque itération, != EOF permet d'arrêter lorsque le fichier est fini
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
            case '\r': 
                break; // ignorer les blancs et sauts de ligne
            default:
                printf("Commande inconnue : %c\n", commande);
                break;
        }
        afficher_entrepot(partie);
    }

    // ferme le fichier ouvert avec fopen
    if (fclose(fichier) != 0) {
    printf("Erreur à la fermeture du fichier.\n");
    }

}

void deplacement(Partie* partie, char* echap){

    char direction;
    printf("dans quelle direction va se déplacer le robot ?");
    scanf(" %c", &direction);
    *echap = direction;
    
    if (*echap == 'p') return;
    switch (direction) {
        case 'd':
            printf("on veut déplacer le robot à droite\n");
            deplacement_D(partie);
            break;
        case 'q':
            printf("on veut déplacer le robot à gauche\n");
            deplacement_G(partie);
            break;
        case 'z':
            printf("on veut déplacer le robot en haut\n");
            deplacement_H(partie);
            break;
        case 's':
            printf("on veut déplacer le robot en bas\n");
            deplacement_B(partie);
            break;
        default:
            printf("mauvaise touche sélectionnée\n");
            break;
    }
}

/* Fonction qui vérifie que le robot peut se déplacer (il ne peut déplacer de mur, il peut déplacer des boites, il ne peut déplacer une boite si sa position d'arrivée est un mur) */

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
    
    
    // Vérification des limites de l'entrepôt
    if (yFrom + comptBoite + 1 >= NB_LIGNE) {
        printf("Déplacement impossible, limite de l'entrepôt\n");
        return;
    }
    
    if (plateau[xFrom][yFrom + comptBoite + 1].e == caseDeChemin){
        plateau[xFrom][yFrom + comptBoite + 1].e = boite;
        plateau[xFrom][yFrom+ 1].e = robot;
        plateau[xFrom][yFrom].e = caseDeChemin;
        partie->coup.yFrom = yFrom + 1;

    }else {
    printf("Déplacement impossible, le robot est bloquée\n");
    }

}

/* Fonction qui vérifie que le robot peut se déplacer (il ne peut déplacer de mur, il peut déplacer des boites, il ne peut déplacer une boite si sa position d'arrivée est un mur) */

void deplacement_G(Partie* partie){

    Case** plateau = partie->entrepot;
    int xFrom = partie->coup.xFrom;
    int yFrom = partie->coup.yFrom;
    
    int comptBoite = 0;
    int i = yFrom - 1;
    while (i >=0 && plateau[xFrom][i].e == boite) {
        comptBoite++;
        i--;
    }
    
    // Vérification des limites de l'entrepôt
    if (yFrom - comptBoite - 1 < 0) {
        printf("Déplacement impossible, limite de l'entrepôt\n");
        return;
    }
    
    if (plateau[xFrom][yFrom - comptBoite - 1].e == caseDeChemin){
        plateau[xFrom][yFrom - comptBoite - 1].e = boite;
        plateau[xFrom][yFrom - 1].e = robot;
        plateau[xFrom][yFrom].e = caseDeChemin;
        partie->coup.yFrom = yFrom - 1;

    }else {
    printf("Déplacement impossible, le robot est bloquée\n");
    }


}

/* Fonction qui vérifie que le robot peut se déplacer (il ne peut déplacer de mur, il peut déplacer des boites, il ne peut déplacer une boite si sa position d'arrivée est un mur) */

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
    
    // Vérification des limites de l'entrepôt
    if (xFrom + comptBoite + 1 >= NB_LIGNE) {
        printf("Déplacement impossible, limite de l'entrepôt\n");
        return;
    }
    
    if (plateau[xFrom + comptBoite + 1][yFrom].e == caseDeChemin){
        plateau[xFrom + comptBoite + 1][yFrom].e = boite;
        plateau[xFrom + 1][yFrom].e = robot;
        plateau[xFrom][yFrom].e = caseDeChemin;
        partie->coup.xFrom = xFrom + 1;

    }else {
    printf("Déplacement impossible, le robot est bloquée\n");
    }

}

/* Fonction qui vérifie que le robot peut se déplacer (il ne peut déplacer de mur, il peut déplacer des boites, il ne peut déplacer une boite si sa position d'arrivée est un mur) */

void deplacement_H(Partie* partie){

    Case** plateau = partie->entrepot;
    int xFrom = partie->coup.xFrom;
    int yFrom = partie->coup.yFrom;
    
    int comptBoite = 0;
    int i = xFrom - 1;
    while (i >=0 && plateau[i][yFrom].e == boite) {
        comptBoite++;
        i--;
    }
    
    // Vérification des limites de l'entrepôt
    if (xFrom - comptBoite - 1 < 0) {
        printf("Déplacement impossible, limite de l'entrepôt\n");
        return;
    }
    
    if (plateau[xFrom - comptBoite - 1][yFrom].e == caseDeChemin){
        plateau[xFrom - comptBoite - 1][yFrom].e = boite;
        plateau[xFrom - 1][yFrom].e = robot;
        plateau[xFrom][yFrom].e = caseDeChemin;
        partie->coup.xFrom = xFrom - 1;

    }else {
    printf("Déplacement impossible, le robot est bloquée\n");
    }

}
