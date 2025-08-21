#include "declaration.h"


void deplacement_H_elargie(Partie* partie){
    
    Case** plateau = partie->entrepot;

    // faire une copie
    Case** enregistrement_plateau = copier_plateau(plateau, partie->hauteur, partie->largeur);
    if (!enregistrement_plateau) {
        fprintf(stderr, "Erreur allocation copie du plateau\n");
        return;
    }

    int x = partie->coup.xFrom;
    int y = partie->coup.yFrom;
    // on enregistre la position initiale
    partie->coup.start_x = partie->coup.xFrom;
    partie->coup.start_y = partie->coup.yFrom;
    int nb_robot = 1;
    partie->coup.fin = 4;
    
    // on créé une liste chaînée
    Liste* l = creer_liste();
    
    
    // on étudie le cas où il y a des boites sous le robot et on ne s'intéressera qu'à [ car il y aura forcement un ] à droite
    if (plateau[x - 1][y - 1].e == boiteG 
    && plateau[x - 2][y - 1].e != mur && plateau[x - 2][y].e != mur){
            nb_robot = 2;
            plateau[x][y].e = caseDeChemin;
            plateau[x - 1][y].e = robot;
            partie->coup.xFrom --;
        }
    if (plateau[x - 1][y].e == boiteG 
    && plateau[x - 2][y].e != mur && plateau[x - 2][y + 1].e != mur){
            nb_robot = 2;
            plateau[x][y].e = caseDeChemin;
            plateau[x - 1][y + 1].e = robot;
            partie->coup.xFrom --;
            partie->coup.yFrom ++;
        }
    // On gère les déplacements qui n'impliquent pas de boite ici
    if (plateau[x - 1][y].e == caseDeChemin) {
        plateau[x][y].e = caseDeChemin;
        plateau[x - 1][y].e = robot;
        partie->coup.xFrom --;
        partie->coup.fin = 7;
        return;
    }
    
    // si on avait une boite sous le robot alors cette fonction toute les boites sous le robot [] devient [@
    R_deplacement_H_elargie(partie, l, enregistrement_plateau);
    
    // si on avait une boite sous le robot alors toute ces boites sont [@ donc maintenant on les fait se déplacer vers le haut en commençant par le haut
    if (partie->coup.fin == 5 || partie->coup.fin == 4){
        deplacement_H_elargie_affichage(partie);
    }
    
    // on met le robot au bon endroit à la fin
    // remettre le robot au bon endroit
    if (nb_robot == 2 && partie->coup.fin == 5){
        partie->coup.xFrom = partie->coup.start_x - 1;
        partie->coup.yFrom = partie->coup.start_y;
        plateau[partie->coup.xFrom][partie->coup.yFrom].e = robot;
    }
    if (nb_robot == 2 && partie->coup.fin == 6){
        partie->coup.xFrom = partie->coup.start_x;
        partie->coup.yFrom = partie->coup.start_y;
        plateau[partie->coup.xFrom][partie->coup.yFrom].e = robot;
    }
    
    // on supprime l'espace alloué à la liste chaînée
    liberer_liste(l);
    liberer_entrepot_enregistre(enregistrement_plateau, partie->hauteur);
}

void R_deplacement_H_elargie(Partie* partie, Liste* l, Case** enregistrement_plateau){
    
    Case** plateau = partie->entrepot;
    int x = partie->coup.xFrom;
    int y = partie->coup.yFrom;
    
    // 1 if pour si ce n'est pas bon il nous reste plus qu'à remettre l'entrepôt comme avant
    if (deplacement_haut_possible(partie) == 1) {
        // on restaure l'ancien entrepôt
        for (int i = 0; i < partie->hauteur; i++) {
            memcpy(plateau[i], enregistrement_plateau[i], partie->largeur * sizeof(Case));
        }
    }
    
    // 1 if pour si c'est bon il nous reste plus qu'à déplacer les boites ( [@ ) vers le bas
    if ((plateau[x - 1][y].e != boiteG && plateau[x - 1][y - 1].e != boiteG && plateau[x - 1][y - 2].e != boiteG) && liste_vide(l)){
    
        partie->coup.fin = 5;
        return;
    }
    
    // 1 if pour si c'est bon mais il nous reste des robots fantômes qu'on à pas testé
    if ((plateau[x - 1][y].e != boiteG && plateau[x - 1][y - 1].e != boiteG && plateau[x - 1][y - 2].e != boiteG) 
    && (!liste_vide(l))
    && (partie->coup.fin == 4)){
        
        retirer_coup(l, partie);
        R_deplacement_H_elargie(partie,l,enregistrement_plateau);
    }
    if ((plateau[x - 1][y - 1].e == boiteG) 
    && (plateau[x - 2][y - 1].e != mur && plateau[x - 2][y].e != mur)
    && (partie->coup.fin == 4)){
        plateau[x - 1][y].e = robot;
        partie->coup.xFrom --;
        x --;
        R_deplacement_H_elargie(partie,l,enregistrement_plateau);
    }
    
    if ((plateau[x - 1][y].e == boiteG && plateau[x - 1][y - 2].e == boiteG && plateau[x - 1][y - 1].e == boiteD)
    && (plateau[x - 2][y].e != mur && plateau[x - 2][y + 1].e != mur && plateau[x - 2][y - 1].e != mur && plateau[x - 2][y - 2].e != mur)
    && (partie->coup.fin == 4)){
        plateau[x - 1][y + 1].e = robot;
        plateau[x - 1][y - 1].e = robot;
        partie->coup.xFrom --;
        partie->coup.yFrom --;
        x --;
        y --;
        
        // on enregistre la position du deuxième robot qu'on ne tester pas dans la liste chaînée
        ajouter_coup(l, partie->coup.xFrom, partie->coup.yFrom + 2);
        
        R_deplacement_H_elargie(partie,l,enregistrement_plateau);
    }
    
    if ((plateau[x - 1][y].e == boiteG && plateau[x - 1][y - 2].e == boiteG && plateau[x - 1][y - 1].e == robot)
    && (plateau[x - 2][y].e != mur && plateau[x - 2][y + 1].e != mur && plateau[x - 2][y - 1].e != mur && plateau[x - 2][y - 2].e != mur)
    && (partie->coup.fin == 4)){
        plateau[x - 1][y + 1].e = robot;
        partie->coup.xFrom --;
        partie->coup.yFrom ++;
        x --;
        y ++;
        
        R_deplacement_H_elargie(partie,l,enregistrement_plateau);
    }
    
    if ((plateau[x - 1][y].e == boiteG && plateau[x - 1][y + 1].e == boiteD) 
    && (plateau[x - 2][y].e != mur && plateau[x - 2][y + 1].e != mur) 
    && (partie->coup.fin == 4)){
        plateau[x - 1][y + 1].e = robot;
        partie->coup.xFrom --;
        partie->coup.yFrom ++;
        x --;
        y ++;
        
        R_deplacement_H_elargie(partie,l,enregistrement_plateau);
    }
    if ((plateau[x - 1][y - 2].e == boiteG && plateau[x - 1][y - 1].e == boiteD)
    && (plateau[x - 2][y - 2].e != mur && plateau[x - 2][y - 1].e != mur) 
    && (partie->coup.fin == 4)){
        plateau[x - 1][y - 1].e = robot;
        partie->coup.xFrom --;
        partie->coup.yFrom --;
        x --;
        y --;
        
        R_deplacement_H_elargie(partie,l,enregistrement_plateau);
    }
}


void deplacement_H_elargie_affichage(Partie* partie){
    Case** plateau = partie->entrepot;
    
    for (int x = 1; x < partie->hauteur - 2; x++){
        for (int y = 2; y < partie->largeur - 3; y++){
            if (plateau[x][y].e == boiteG && plateau[x][y + 1].e == robot){
                plateau[x][y].e = caseDeChemin;
                plateau[x][y + 1].e = caseDeChemin;
                plateau[x - 1][y].e = boiteG;
                plateau[x - 1][y + 1].e = boiteD;
            }
        }
    }
}


int deplacement_haut_possible(Partie* partie){

    int x = partie->coup.xFrom;
    int y = partie->coup.yFrom;
    Case** plateau = partie->entrepot;
    
    if (
        (plateau[x - 1][y].e == mur) || // cas 1

        (plateau[x - 1][y - 1].e == boiteG && (plateau[x - 2][y - 1].e == mur || plateau[x - 2][y].e == mur)) || // cas 2 et 5

        (plateau[x - 1][y].e == boiteG && (plateau[x - 2][y].e == mur || plateau[x - 2][y + 1].e == mur)) || // cas 3

        (plateau[x][y - 1].e == boiteG && plateau[x - 1][y].e == boiteG &&
            (plateau[x][y - 1].e == mur || plateau[x - 2][y].e == mur || plateau[x - 2][y + 1].e == mur)) || // cas 4

        (plateau[x][y - 1].e == boiteG && plateau[x - 1][y - 2].e == boiteG &&
            (plateau[x - 1][y].e == mur || plateau[x - 2][y - 2].e == mur || plateau[x - 2][y - 1].e == mur)) || // cas 6

        (plateau[x][y - 1].e == boiteG && plateau[x - 1][y].e == boiteG && plateau[x - 1][y - 2].e == boiteG &&
            (plateau[x - 2][y - 2].e == mur || plateau[x - 2][y - 1].e == mur || plateau[x - 2][y].e == mur || plateau[x - 2][y + 1].e == mur)) // cas 7
    ){
        printf("Un mur bloque le déplacement vers le haut\n");
        partie->coup.fin = 6;
        return 1;
    }
    return 0;
}
