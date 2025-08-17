#include "declaration.h"

void deplacement_vers_le_bas_test(Partie* partie){
    
    Case** plateau = partie->entrepot;
    int x = partie->coup.xFrom;
    int y = partie->coup.yFrom;
    int start_x = partie->coup.xFrom;
    int start_y = partie->coup.yFrom;
    int nb_robot = 1;
    
    printf("0. x : %d, y : %d\n",x,y);
    
    /*
    printf("1.\n");
    afficher_entrepot(partie);
    plateau[x + 2][y].e;
    partie->coup.xFrom;
    partie->hauteur;
    partie->largeur;
    */
    
    // on étudie le cas où il y a des boites sous le robot et on ne s'interessera qu'à [ car il y aura forcement un ] à droite
    if (plateau[x + 1][y - 1].e == boiteG 
    && plateau[x + 2][y - 1].e != mur && plateau[x + 2][y].e != mur){
            nb_robot = 2;
            plateau[x][y].e = caseDeChemin;
            plateau[x + 1][y].e = robot;
            partie->coup.xFrom ++;
        }
    if (plateau[x + 1][y].e == boiteG 
    && plateau[x + 2][y].e != mur && plateau[x + 2][y + 1].e != mur){
            nb_robot = 2;
            plateau[x][y].e = caseDeChemin;
            plateau[x + 1][y + 1].e = robot;
            partie->coup.xFrom ++;
            partie->coup.yFrom ++;
        }
    // On gère les déplacements qui n'impliquent pas de boite ici
        if (plateau[x + 1][y].e == caseDeChemin) {
            // on déplace le robot
            printf("1. x : %d, y : %d\n",x,y);
            afficher_entrepot(partie);
            plateau[x][y].e = caseDeChemin;
            plateau[x + 1][y].e = robot;
            partie->coup.xFrom ++;
            printf("2. x : %d, y : %d\n",x,y);
            afficher_entrepot(partie);
            return;
        }
    
    R_deplacement_vers_le_bas_test_recu(partie, nb_robot);
    afficher_entrepot(partie);
    deplacement_vers_le_bas_test_recu(partie);
    
    // on met bien le robot à la fin
    partie->coup.xFrom = start_x + 1;
    partie->coup.yFrom = start_y;
    
}

void R_deplacement_vers_le_bas_test_recu(Partie* partie, int nb_robot){
    
    Case** plateau = partie->entrepot;
    int x = partie->coup.xFrom;
    int y = partie->coup.yFrom;
    printf("3. x : %d, y : %d\n",x,y);
    afficher_entrepot(partie);
    
    /*
    printf("1.\n");
    afficher_entrepot(partie);
    plateau[x + 2][y].e;
    partie->coup.xFrom;
    partie->hauteur;
    partie->largeur;
    */
    
    // while (nb_robot != 1){
        // 2eme rangé après le robot
        if ((plateau[x + 1][y].e != boiteG && plateau[x + 1][y - 1].e != boiteG && plateau[x + 1][y - 2].e != boiteG) && coordonee == NULL){
            printf("c'est bon");
            return;
        }
        if ((plateau[x + 1][y].e != boiteG && plateau[x + 1][y - 1].e != boiteG && plateau[x + 1][y - 2].e != boiteG) && coordonee != NULL){
            // on met le robot qui n'est pas fantôme et qui attendait en action
            printf("c'est bon pour le moment");
            return;
        }
        if (plateau[x + 1][y - 1].e == boiteG 
        && plateau[x + 2][y - 1].e != mur && plateau[x + 2][y].e != mur){
            printf("4. x : %d, y : %d\n",x,y);
            afficher_entrepot(partie);
            nb_robot ++;
            plateau[x + 1][y].e = robot;
            partie->coup.xFrom ++;
            R_deplacement_vers_le_bas_test_recu(partie, nb_robot);
        }
        if (plateau[x + 1][y].e == boiteG && plateau[x + 1][y - 2].e == boiteG 
        && plateau[x + 2][y].e != mur && plateau[x + 2][y + 1].e != mur && plateau[x + 2][y - 1].e != mur && plateau[x + 2][y - 2].e != mur){
            printf("5. x : %d, y : %d\n",x,y);
            afficher_entrepot(partie);
            nb_robot = nb_robot + 2;
            plateau[x + 1][y + 1].e = robot;
            plateau[x + 1][y - 1].e = robot;
            partie->coup.xFrom ++;
            partie->coup.yFrom --;
            R_deplacement_vers_le_bas_test_recu(partie, nb_robot);
            // on met les coordonnée du deuxième robot en attente
        }
        if ((plateau[x + 1][y].e == boiteG) && (plateau[x + 2][y].e != mur && plateau[x + 2][y + 1].e != mur)){
            printf("6. x : %d, y : %d\n",x,y);
            afficher_entrepot(partie);
            nb_robot ++;
            plateau[x + 1][y + 1].e = robot;
            partie->coup.xFrom ++;
            partie->coup.yFrom ++;
            R_deplacement_vers_le_bas_test_recu(partie, nb_robot);
        }
        if (plateau[x + 1][y - 2].e == boiteG 
        && plateau[x + 2][y - 2].e != mur && plateau[x + 2][y - 1].e != mur){
            printf("7. x : %d, y : %d\n",x,y);
            afficher_entrepot(partie);
            nb_robot ++;
            plateau[x + 1][y - 1].e = robot;
            partie->coup.xFrom ++;
            partie->coup.yFrom --;
            R_deplacement_vers_le_bas_test_recu(partie, nb_robot);
        }
    //}
}

void deplacement_vers_le_bas_test_recu(Partie* partie){
    Case** plateau = partie->entrepot;
    printf("partie->largeur : %d, partie->hauteur : %d ",partie->largeur,partie->hauteur);
    for (int y = 1; y < partie->largeur - 3; y++){
        for (int x = partie->hauteur - 3; x >= 1; x--){
            if (plateau[x][y].e == boiteG && plateau[x][y + 1].e == robot){
                plateau[x][y].e = caseDeChemin;
                plateau[x][y + 1].e = caseDeChemin;
                plateau[x + 1][y].e = boiteG;
                plateau[x + 1][y + 1].e = boiteD;
            }
        }
    }
}
