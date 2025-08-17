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
    printf("dans quelle direction va se déplacer le robot ? ");
    scanf(" %c", &direction);
    *echap = direction;
    partie->coup.compt = 0;

    if (*echap == 'p') return;

    switch (direction) {
        case 'd': printf("on veut déplacer le robot à droite\n"); deplacement_D_elargie(partie); break;
        case 'q': printf("on veut déplacer le robot à gauche\n"); deplacement_G_elargie(partie); break;
        case 'z': printf("on veut déplacer le robot en haut\n"); deplacement_H_elargie(partie); break;
        case 's': printf("on veut déplacer le robot en bas\n"); deplacement_vers_le_bas_test(partie); break;
        default: printf("mauvaise touche sélectionnée\n"); break;
    }
}


// Fonction principale pour gérer le déplacement vers le bas
void deplacement_vers_le_bas(Partie* partie, int x, int y) {

    Case** plateau = partie->entrepot;
    
    // On gère les déplacements qui impliquent des boites ici (dont celle sous le robot est une [
    if (plateau[x + 1][y].e == boiteG && plateau[x + 2][y].e != mur && plateau[x + 2][y + 1].e != mur) {
    // on a [ sous le robot, pas de mur sous le [ et le ]
        if (plateau[x + 2][y].e == caseDeChemin && plateau[x + 2][y + 1].e == caseDeChemin) {
            // il y a des cases de chemin après [ et ] => on déplace le robot et la []
            printf("1.\n");
            afficher_entrepot(partie);
            // on déplace les boites
            plateau[x + 2][y].e = boiteG;
            plateau[x + 2][y + 1].e = boiteD;
            plateau[x + 1][y + 1].e = caseDeChemin;
            // on déplace le robot
            plateau[x + 1][y].e = robot;
            plateau[x][y].e = caseDeChemin;
            partie->coup.xFrom = x + 1;
            x ++;
            printf("2.\n");
            afficher_entrepot(partie);
            if (partie->coup.compt != 0){
                // on déplace le robot en x - 2
                plateau[x - 2][y].e = robot;
                plateau[x][y].e = caseDeChemin;
                partie->coup.xFrom = x - 2;
                x = x - 2;
                printf("6. %d\n", partie->hauteur);
                afficher_entrepot(partie);
            }else{
                printf("7.\n");
                return;
            }
        }
        if (plateau[x + 2][y].e == boiteG) {
            // on a au moins deux [ sous le robot
            printf("3.\n");
            afficher_entrepot(partie);
            // on déplace le robot en x + 1
            plateau[x + 1][y].e = robot;
            plateau[x][y].e = caseDeChemin;
            partie->coup.xFrom = x + 1;
            x ++;
            // on enregistre le coordonnée du robot précédent
            partie->coup.last_x = x - 1;
            partie->coup.last_y = y;
            printf("4.\n");
            afficher_entrepot(partie);
            partie->coup.compt ++;
            deplacement_vers_le_bas(partie, x, y);
        }
    }
    
    // On gère les déplacements qui n'impliquent pas de boite ici
    if (plateau[x + 1][y].e == caseDeChemin && partie->coup.compt == 0) {
        // Déplacement du robot
        printf("5.\n");
        printf("x = %d\n",x);
        afficher_entrepot(partie);
        // on déplace le robot
        plateau[x + 1][y].e = robot;
        x ++;
        plateau[x][y].e = caseDeChemin;
        partie->coup.xFrom = x + 1;
        return;
    }
}

// Fonction pour vérifier le déplacement vers le bas avec une boiteG
void verif_deplacement_B_G(Partie* partie, int x, int y) {

    Case** plateau = partie->entrepot;
    printf("x = %d, y = %d\n",x,y);
    if (plateau[x + 1][y].e == boiteG) {
    printf("On repère une [ sous la [1.\n");
        if (plateau[x + 2][y].e != mur && plateau[x + 2][y + 1].e != mur &&
            plateau[x + 2][y].e == caseDeChemin && plateau[x + 2][y + 1].e == caseDeChemin) {
            // Il n'y a pas de mur et il y a des cases de chemin après donc condition de sortie c'est bon
            printf("Déplacement possible vers le bas 4.\n");
            // on met un robot fantôme sur la place plateau[x + 1][y].e pour qu'il déplace la boite mais il faut pas oublier le cotée droit donc rebelote sur plateau[x + 1][y + 1].e
        }
        if (plateau[x + 2][y].e != mur && plateau[x + 2][y + 1].e != mur &&
            plateau[x + 2][y].e == boiteG) {
            // Il n'y a pas de mur et il y a [ après donc on fait un appel récursif
            verif_deplacement_B_G(partie, x + 1, y);
        }
    }
}

// Fonction pour vérifier le déplacement vers le bas avec une boiteD
void verif_deplacement_B_D(Partie* partie, int x) {

    Case** plateau = partie->entrepot;
    int y = 0; // Supposons que y est défini quelque part, sinon il faut le passer en paramètre

    if (plateau[x + 1][y].e == boiteD) {
        if (plateau[x + 2][y].e != mur && plateau[x + 2][y - 1].e != mur &&
            plateau[x + 2][y].e == caseDeChemin && plateau[x + 2][y - 1].e == caseDeChemin) {
            // Il n'y a pas de mur et il y a des cases de chemin après donc condition de sortie c'est bon
            printf("Déplacement possible vers le bas 5.\n");
        }
        if (plateau[x + 2][y].e != mur && plateau[x + 2][y - 1].e != mur &&
            plateau[x + 2][y].e == boiteD) {
            // Il n'y a pas de mur et il y a [ après donc on fait un appel récursif
            verif_deplacement_B_G(partie, x + 1,y);
        }
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

void deplacement_D_elargie(Partie* partie) {
    Case** plateau = partie->entrepot;
    int x = partie->coup.xFrom;
    int y = partie->coup.yFrom;

    // Si la case à droite est vide -> robot avance seul
    if (plateau[x][y + 1].e == caseDeChemin) {
        plateau[x][y + 1].e = robot;
        plateau[x][y].e = caseDeChemin;
        partie->coup.yFrom = y + 1;
        printf("Déplacement robot seul vers la droite.\n");
        return;
    }

    // Si c’est une boîte à droite
    if (plateau[x][y + 1].e == boiteG) {
        int yCourant = y + 1;
        int nbPaires = 0;

        // Compter toutes les paires [] alignées
        while (yCourant + 1 < partie->largeur &&
               plateau[x][yCourant].e == boiteG &&
               plateau[x][yCourant + 1].e == boiteD) {
            nbPaires++;
            yCourant += 2;
        }

        // Vérifier que la case juste après la dernière paire est vide
        if (yCourant < partie->largeur && plateau[x][yCourant].e == caseDeChemin) {
            printf("Poussée de %d paire(s) [] vers la droite.\n", nbPaires);
            // Décaler toutes les paires vers la droite (en partant de la fin)
            for (int i = nbPaires - 1; i >= 0; i--) {
                int posG = y + 1 + i * 2;
                int posD = posG + 1;
                plateau[x][posD + 1].e = boiteD;
                plateau[x][posG + 1].e = boiteG;
            }
            // Déplacer le robot
            plateau[x][y + 1].e = robot;
            plateau[x][y].e = caseDeChemin;
            partie->coup.yFrom = y + 1;
        } else {
            printf("Déplacement impossible, obstacle après la dernière boîte.\n");
        }
        return;
    }

    printf("Déplacement impossible.\n");
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
