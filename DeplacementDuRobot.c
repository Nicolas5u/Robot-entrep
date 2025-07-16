#include "declaration.h"

/* ***************************************************

Programme qui contient les fonctions nécessaires aux déplacements du robots

*************************************************** */

/* Fonction qui vérifie que le robot peut se déplacer (il ne peut déplacer de mur, il peut déplacer des boites, il ne peut déplacer une boite si sa position d'arrivée est un mur) */

void deplacement(Partie* partie){
    char direction;
    printf("dans quelle direction va se déplacer le robot ?");
    scanf("%c", &direction);
    switch (direction) {
        case 'd':
            printf("on veut déplacer le robot à droite");
            deplacementD(partie);
            break;
        case 'q':
            printf("on veut déplacer le robot à gauche");
            break;
        case 'z':
            printf("on veut déplacer le robot en haut");
            break;
        case 's':
            printf("on veut déplacer le robot en bas");
            break;
        default:
            printf("mauvaise touche sélectionnée");
            break;
    }
}

void deplacementD(Partie* partie){
/*
    if(plateau[xFrom+1][yFrom].e == caseDeChemin){                              // rajouter la vérification complet
        plateau[xFrom+1][yFrom].e = robot;
        plateau[xFrom][yFrom].e = caseDeChemin;
        xFrom = xTo;
        }
    if(plateau[xFrom+1][yFrom].e == boite){                              // rajouter la vérification complet
        plateau[xFrom+1][yFrom].e = robot;
        plateau[xFrom][yFrom].e = caseDeChemin;
        xFrom = xTo;
        }
    réflexion :
    j'ai besoin d'un compteur du nombre de boite à droite du robot jusqu'à une case de chemin si c'est jusqu'à une case de mur alors renvoyer que le robot et bloqué et passer à l'étape d'après
    */
    Case** plateau = partie->entrepot;
    int xFrom = partie->coup.xFrom;
    int yFrom = partie->coup.yFrom;

    int comptBoite = 0;
    for (int i = xFrom+1; i < NB_LIGNE; i++){ // pour i de la position de droite du robot jusqu'au mur
        if(plateau[i][yFrom].e == boite){
            comptBoite++;
        }else{
            break;
        }
    }
    plateau[xFrom + comptBoite + 1][yFrom].e = boite;
    plateau[xFrom + 1][yFrom].e = robot;
    
}

/*
void deplacementD(Partie* partie) {
    Case** plateau = partie->entrepot;
    int xFrom = partie->coup.xFrom;
    int yFrom = partie->coup.yFrom;

    // Vérification des limites de déplacement
    if (xFrom + 1 >= NB_LIGNE) {
        printf("Déplacement impossible : bord de la carte.\n");
        return;
    }

    // Vérifier ce qu’il y a à droite du robot
    if (plateau[xFrom + 1][yFrom].e == caseDeChemin) {
        // On déplace le robot
        plateau[xFrom + 1][yFrom].e = robot;
        plateau[xFrom][yFrom].e = caseDeChemin;

        // On met à jour le coup dans la structure partie
        partie->coup.xFrom = xFrom + 1;
    } 
    else if (plateau[xFrom + 1][yFrom].e == boite) {
        // Vérifier s’il y a de la place après la boîte
        if (xFrom + 2 >= NB_LIGNE) {
            printf("Déplacement impossible : pas d’espace pour pousser la boîte.\n");
            return;
        }
        if (plateau[xFrom + 2][yFrom].e == caseDeChemin) {
            // Déplacer la boîte
            plateau[xFrom + 2][yFrom].e = boite;
            // Déplacer le robot
            plateau[xFrom + 1][yFrom].e = robot;
            plateau[xFrom][yFrom].e = caseDeChemin;

            // Mettre à jour la position du robot dans le coup
            partie->coup.xFrom = xFrom + 1;
        } else {
            printf("Déplacement impossible : la boîte est bloquée.\n");
        }
    } 
    else {
        printf("Déplacement impossible : obstacle non gérable.\n");
    }
}
*/
