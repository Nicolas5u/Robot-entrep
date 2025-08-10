#include "declaration.h"

/**
 * @brief Déplace le robot vers la droite si le déplacement est possible.
 * 
 * @param partie Pointeur vers la structure de la partie.
 */

/**
 * @brief Déplace le robot vers le bas si le déplacement est possible.
 * 
 * @param partie Pointeur vers la structure de la partie.
 */
 
void deplacement_elargie(Partie* partie, char* echap){

    char direction;
    printf("dans quelle direction va se déplacer le robot ?");
    scanf(" %c", &direction);
    *echap = direction;

    if (*echap == 'p') return;

    switch (direction) {
        case 'd': printf("on veut déplacer le robot à droite\n"); deplacement_D_elargie(partie); break;
        case 'q': printf("on veut déplacer le robot à gauche\n"); deplacement_G_elargie(partie); break;
        case 'z': printf("on veut déplacer le robot en haut\n"); deplacement_H_elargie(partie); break;
        case 's': printf("on veut déplacer le robot en bas\n"); deplacement_B_elargie(partie); break;
        default: printf("mauvaise touche sélectionnée\n"); break;
    }
}

void deplacement_B_elargie(Partie* partie){
    Case** plateau = partie->entrepot;
    int x = partie->coup.xFrom;
    int y = partie->coup.yFrom;

    int comptBoite = 0;
    int i = x + 1;
    
    // on vérifie simplement si il y a un mur qui bloque les boites mais seulement sur la colonne du robot
    while (i < partie->hauteur && (plateau[i][y].e == boiteG || plateau[i][y].e == boiteD)) {
        comptBoite++;
        i++;
        if (plateau[x + comptBoite + 1][y].e == mur) {printf("Déplacement impossible, un mur bloque sur la colonne du robot\n");}
    }
    printf("le compte des boites à pousser %d", comptBoite);

    // ne marche que pour le déplacement d'une seule boite
    for (int j = 0; j < comptBoite; j++){
        // on vérifie que la boite i peut se déplacer (si cote gauche on vérifie que le droit n'heurtera pas un mur)
        if (plateau[x + comptBoite + 2][y].e =! mur && 
            plateau[x + comptBoite + 2][y + 1].e =! mur && 
            plateau[x + comptBoite + 1][y].e == boiteG){
            
            // c'est ok pour cette boite
            // on test en partant comme si le robot était en [x + comptBoite + 1][y] et [x + comptBoite + 1][y + 1]
        }
            
        
        
        
        if (plateau[x + comptBoite + 1][y].e == caseDeChemin && plateau[x + 1][y].e == boiteG){
            plateau[x + comptBoite + 1][y].e = boiteG;
            plateau[x + comptBoite + 1][y + 1].e = boiteD;
            plateau[x + comptBoite][y + 1].e = caseDeChemin;
            plateau[x + 1][y].e = robot;
            plateau[x][y].e = caseDeChemin;
            partie->coup.xFrom++;
        } 
        if (plateau[x + comptBoite + 1][y].e == caseDeChemin && plateau[x + 1][y].e == boiteD){
            plateau[x + comptBoite + 1][y].e = boiteD;
            plateau[x + comptBoite + 1][y - 1].e = boiteG;
            plateau[x + comptBoite][y - 1].e = caseDeChemin;
            plateau[x + 1][y].e = robot;
            plateau[x][y].e = caseDeChemin;
            partie->coup.xFrom++;
        }
        comptBoite--;
    }
}

/**
 * @brief Déplace le robot vers le haut si le déplacement est possible.
 * 
 * @param partie Pointeur vers la structure de la partie.
 */
void deplacement_H_elargie(Partie* partie){
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

void deplacement_D_elargie(Partie* partie){
    Case** plateau = partie->entrepot;
    int xFrom = partie->coup.xFrom;
    int yFrom = partie->coup.yFrom;

    int comptBoite = 0;
    int i = yFrom + 1;
    while (i < partie->largeur && plateau[xFrom][i].e == boite) {
        comptBoite++;
        i++;
    }

    if (yFrom + comptBoite + 1 >= partie->largeur) {
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
void deplacement_G_elargie(Partie* partie){
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
