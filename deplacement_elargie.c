#include "declaration.h"

/**
 * @brief Gère les déplacements du robot dans l'entrepôt élargi
 * 
 * Demande à l'utilisateur une direction (z, q, s, d) puis appelle la fonction
 * correspondante. Met également à jour la variable echap pour gérer la sortie.
 * 
 * - z : Haut  
 * - s : Bas  
 * - q : Gauche  
 * - d : Droite  
 * - p : Quitter les modes (toujours d'actualité) 
 * 
 * @param partie Pointeur vers la structure de la partie
 * @param echap Pointeur vers la variable de contrôle des touches
 */
void deplacement_elargie(Partie* partie, char* echap) {

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
        case 's': printf("on veut déplacer le robot en bas\n"); deplacement_B_elargie(partie); break;
        default: printf("mauvaise touche sélectionnée\n"); break;
    }
}

/**
 * @brief Déplace le robot vers la droite dans l'entrepôt élargi
 * 
 * - Si la case à droite est libre alors le robot avance seul
 * - Si une boîte (paire `[]`) est rencontrée alors toutes les paires sont poussées vers la droite (si la place est libre)
 * - Si un obstacle bloque alors le déplacement est annulé
 * 
 * @param partie Pointeur vers la structure de la partie
 */
void deplacement_D_elargie(Partie* partie) {
    Case** plateau = partie->entrepot;
    int x = partie->coup.xFrom;
    int y = partie->coup.yFrom;

    // Si la case à droite est vide alors le robot avance seul
    if (plateau[x][y + 1].e == caseDeChemin) {
        plateau[x][y + 1].e = robot;
        plateau[x][y].e = caseDeChemin;
        partie->coup.yFrom = y + 1;
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
            printf("Un mur bloque le déplacement vers la droite\n");
        }
        return;
    }

    printf("Déplacement impossible\n");
}

/**
 * @brief Déplace le robot vers la gauche dans l'entrepôt élargi
 * 
 * - Si la case à gauche est libre alors le robot avance seul.  
 * - Si une boîte (paire `[]`) est rencontrée alors toutes les paires sont poussées vers la gauche (si la place est libre)
 * - Si un obstacle bloque alors le déplacement est annulé
 * 
 * @param partie Pointeur vers la structure de la partie
 */
void deplacement_G_elargie(Partie* partie) {
    Case** plateau = partie->entrepot;
    int x = partie->coup.xFrom;
    int y = partie->coup.yFrom;

    // Si la case à gauche est vide alors le robot avance seul
    if (plateau[x][y - 1].e == caseDeChemin) {
        plateau[x][y - 1].e = robot;
        plateau[x][y].e = caseDeChemin;
        partie->coup.yFrom = y - 1;
        return;
    }

    // Si c’est une boîte à gauche
    if (plateau[x][y - 1].e == boiteD) {
        int yCourant = y - 1;
        int nbPaires = 0;

        // Compter toutes les paires [] alignées vers la gauche
        while (yCourant - 1 >= 0 &&
               plateau[x][yCourant].e == boiteD &&
               plateau[x][yCourant - 1].e == boiteG) {
            nbPaires++;
            yCourant -= 2;
        }

        // Vérifier que la case juste avant la première paire est vide
        if (yCourant >= 0 && plateau[x][yCourant].e == caseDeChemin) {
            // Décaler toutes les paires vers la gauche (en partant de la plus proche du robot)
            for (int i = 0; i < nbPaires; i++) {
                int posD = y - 1 - i * 2;
                int posG = posD - 1;
                plateau[x][posG - 1].e = boiteG;
                plateau[x][posD - 1].e = boiteD;
            }
            // Déplacer le robot
            plateau[x][y - 1].e = robot;
            plateau[x][y].e = caseDeChemin;
            partie->coup.yFrom = y - 1;
        } else {
            printf("Un mur bloque le déplacement vers la gauche\n");
        }
        return;
    }

    printf("Déplacement impossible\n");
}

