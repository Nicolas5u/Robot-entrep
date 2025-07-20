#include "declaration.h"

/* ***************************************************

Programme qui contient les fonctions nécessaires aux déplacements du robots

*************************************************** */

/* Fonction qui vérifie que le robot peut se déplacer (il ne peut déplacer de mur, il peut déplacer des boites, il ne peut déplacer une boite si sa position d'arrivée est un mur) */

void deplacement(Partie* partie, char* echap){
    char direction;
    printf("dans quelle direction va se déplacer le robot ?");
    scanf(" %c", &direction);
    /* méthode pour récupérer la valeur du échap                                                   marche pas et je ne sais pas comment faire 
    direction = getchar(); // Récupère l'entier (code ASCII)
    while (getchar() != '\n'); // vide le buffer (important sinon on lit des caractères résiduels)
    */
    *echap = direction;
    if (*echap == 'p') return;
    switch (direction) {
        case 'd':
            printf("on veut déplacer le robot à droite\n");
            deplacementD(partie->entrepot, partie);
            break;
        case 'q':
            printf("on veut déplacer le robot à gauche\n");
            deplacementG(partie);
            break;
        case 'z':
            printf("on veut déplacer le robot en haut\n");
            deplacementH(partie);
            break;
        case 's':
            printf("on veut déplacer le robot en bas\n");
            deplacementB(partie);
            break;
        default:
            printf("mauvaise touche sélectionnée\n");
            break;
    }
}

void deplacementD(Case** entrepot, Partie* partie){
    int xFrom = partie->coup.xFrom;
    int yFrom = partie->coup.yFrom;
    
    printf(" 1 xFrom = %d et yFrom = %d\n",xFrom,yFrom);
    
    int comptBoite = 0;
    int i = yFrom + 1;
    
    printf(" 2 xFrom = %d et yFrom = %d\n",xFrom,yFrom);
    
    while (i < NB_LIGNE && entrepot[xFrom][i].e == boite) {
        comptBoite++;
        i++;
    }
    
    printf(" 3 comptBoite = %d\n",comptBoite);
    
    // Vérification des limites de l'entrepôt
    if (yFrom + comptBoite + 1 >= NB_LIGNE) {
        printf("Déplacement impossible, limite de l'entrepôt\n");
        printf(" 4 xFrom = %d et yFrom = %d\n",xFrom,yFrom);
        return;
    }
    
    if (entrepot[xFrom][yFrom + comptBoite + 1].e == caseDeChemin){
        entrepot[xFrom][yFrom + comptBoite + 1].e = boite;
        entrepot[xFrom][yFrom+ 1].e = robot;
        entrepot[xFrom][yFrom].e = caseDeChemin;
        partie->coup.yFrom = yFrom + 1;
        printf(" 5 xFrom = %d et yFrom = %d\n",xFrom,yFrom);

    }else {
    printf("Déplacement impossible, le robot est bloquée\n");
    printf(" 6 xFrom = %d et yFrom = %d\n",xFrom,yFrom);
    }

}

void deplacementG(Partie* partie){

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

void deplacementB(Partie* partie){

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

void deplacementH(Partie* partie){

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
