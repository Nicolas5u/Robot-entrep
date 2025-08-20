#include "declaration.h"


void deplacement_vers_le_bas_test(Partie* partie){
    
    Case** plateau = partie->entrepot;
    int x = partie->coup.xFrom;
    int y = partie->coup.yFrom;
    // on enregistre la position initial du robot pour pouvoir le placer proprement à la fin de la fonction
    partie->coup.start_x = partie->coup.xFrom;
    partie->coup.start_y = partie->coup.yFrom;
    // variable
    int nb_robot = 1;
    partie->coup.fin = 4;
    
    // on créé une liste chaînée                                             MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
    Liste* l = creer_liste();
    
    printf("0. x : %d, y : %d\n",x,y);
    
    
    // on étudie le cas où il y a des boites sous le robot et on ne s'intéressera qu'à [ car il y aura forcement un ] à droite
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
    
    // si on avait une boite sous le robot alors cette fonction toute les boites sous le robot [] devient [@
    R_deplacement_vers_le_bas_test_recu(partie, nb_robot, l);
    afficher_entrepot(partie);
    
    // si on avait une boite sous le robot alors toute ces boites sont [@ donc maintenant on les fait se déplacer vers le bas en commençant par le bas
    deplacement_vers_le_bas_test_recu(partie);
    printf("10. x : %d, y : %d\n",partie->coup.xFrom,partie->coup.yFrom);
    afficher_entrepot(partie);
    
    // on met le robot au bon endroit à la fin
    printf("10. x : %d, y : %d\n",partie->coup.start_x,partie->coup.start_y);
    partie->coup.xFrom = partie->coup.start_x +1;
    partie->coup.yFrom = partie->coup.start_y;
    plateau[partie->coup.xFrom][partie->coup.yFrom].e = robot;
    printf("10. x : %d, y : %d\n",partie->coup.xFrom,partie->coup.yFrom);
    afficher_entrepot(partie);
    
    // on supprime l'espace alloué à la liste chaînée                                             MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
    liberer_liste(l);
}

void R_deplacement_vers_le_bas_test_recu(Partie* partie, int nb_robot, Liste* l){
    
    Case** plateau = partie->entrepot;
    int x = partie->coup.xFrom;
    int y = partie->coup.yFrom;
    printf("3. x : %d, y : %d\n",x,y);
    afficher_entrepot(partie);
    
    
    
    // 2eme rangé après le robot
    if ((plateau[x + 1][y].e != boiteG && plateau[x + 1][y - 1].e != boiteG && plateau[x + 1][y - 2].e != boiteG) && liste_vide(l)){
        printf("c'est bon\n");
        partie->coup.fin = 5;
        return;
    }
    if ((plateau[x + 1][y].e != boiteG && plateau[x + 1][y - 1].e != boiteG && plateau[x + 1][y - 2].e != boiteG) && !liste_vide(l)){
        // on met le robot qui n'est pas fantôme et qui attendait en action
        printf("c'est bon pour le moment\n");
        printf("8a. x : %d, y : %d\n",x,y);
        
        // on met à jour la position du robot des tests sur les robots qui n'avait pas pu être testé                                      MMMMMMMMMMMMMMMMMMMMMMMp
        
        retirer_coup(l, partie);
        afficher_liste(l);
        
        R_deplacement_vers_le_bas_test_recu(partie, nb_robot,l);
    }
    if (plateau[x + 1][y - 1].e == boiteG 
    && plateau[x + 2][y - 1].e != mur && plateau[x + 2][y].e != mur){
        printf("4. x : %d, y : %d\n",x,y);
        afficher_entrepot(partie);
        nb_robot ++;
        plateau[x + 1][y].e = robot;
        partie->coup.xFrom ++;
        x ++;
        printf("4. x : %d, y : %d\n",x,y);
        R_deplacement_vers_le_bas_test_recu(partie, nb_robot,l);
    }
    if (plateau[x + 1][y].e == boiteG && plateau[x + 1][y - 2].e == boiteG && plateau[x + 1][y - 1].e == boiteD
    && plateau[x + 2][y].e != mur && plateau[x + 2][y + 1].e != mur && plateau[x + 2][y - 1].e != mur && plateau[x + 2][y - 2].e != mur){
        printf("5a. x : %d, y : %d\n",x,y);
        afficher_entrepot(partie);
        nb_robot = nb_robot + 2;
        plateau[x + 1][y + 1].e = robot;
        plateau[x + 1][y - 1].e = robot;
        partie->coup.xFrom ++;
        partie->coup.yFrom --;
        x ++;
        y --;
        printf("5b. x : %d, y : %d\n",x,y);
        
        // on enregistre la position du deuxième robot qu'on ne tester pas dans la liste chaînée         MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
        ajouter_coup(l, partie->coup.xFrom, partie->coup.yFrom +2);
        afficher_liste(l);
        
        R_deplacement_vers_le_bas_test_recu(partie, nb_robot,l);
        
    }
    if (plateau[x + 1][y].e == boiteG && plateau[x + 1][y - 2].e == boiteG && plateau[x + 1][y - 1].e == robot
    && plateau[x + 2][y].e != mur && plateau[x + 2][y + 1].e != mur && plateau[x + 2][y - 1].e != mur && plateau[x + 2][y - 2].e != mur
    && partie->coup.fin == 4){
        printf("9a. x : %d, y : %d\n",x,y);
        afficher_entrepot(partie);
        nb_robot ++;
        plateau[x + 1][y + 1].e = robot;
        partie->coup.xFrom ++;
        partie->coup.yFrom ++;
        x ++;
        y ++;
        printf("9b. x : %d, y : %d\n",x,y);
        printf("9c. x : %d, y : %d\n",partie->coup.xFrom,partie->coup.yFrom);
        
        R_deplacement_vers_le_bas_test_recu(partie, nb_robot,l);
        
    }
    if ((plateau[x + 1][y].e == boiteG && plateau[x + 1][y + 1].e == boiteD) && (plateau[x + 2][y].e != mur && plateau[x + 2][y + 1].e != mur)){
        printf("6a. x : %d, y : %d\n",x,y);
        afficher_entrepot(partie);
        nb_robot ++;
        plateau[x + 1][y + 1].e = robot;
        partie->coup.xFrom ++;
        partie->coup.yFrom ++;
        x ++;
        y ++;
        printf("6b. x : %d, y : %d\n",x,y);
        R_deplacement_vers_le_bas_test_recu(partie, nb_robot,l);
    }
    if (plateau[x + 1][y - 2].e == boiteG && plateau[x + 1][y - 1].e == boiteD
    && plateau[x + 2][y - 2].e != mur && plateau[x + 2][y - 1].e != mur){
        printf("7a. x : %d, y : %d\n",x,y);
        afficher_entrepot(partie);
        nb_robot ++;
        plateau[x + 1][y - 1].e = robot;
        partie->coup.xFrom ++;
        partie->coup.yFrom --;
        x ++;
        y --;
        printf("7b. x : %d, y : %d\n",x,y);
        R_deplacement_vers_le_bas_test_recu(partie, nb_robot,l);
    }
}

void deplacement_vers_le_bas_test_recu(Partie* partie){
    Case** plateau = partie->entrepot;
    printf("partie->largeur : %d, partie->hauteur : %d\n",partie->largeur,partie->hauteur);
    for (int x = partie->hauteur - 3; x >= 1; x--){
        for (int y = 2; y < partie->largeur - 3; y++){
            if (plateau[x][y].e == boiteG && plateau[x][y + 1].e == robot){
                plateau[x][y].e = caseDeChemin;
                plateau[x][y + 1].e = caseDeChemin;
                plateau[x + 1][y].e = boiteG;
                plateau[x + 1][y + 1].e = boiteD;
            }
        }
    }
}
