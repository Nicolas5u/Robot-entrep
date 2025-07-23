#include "declaration.h"

/* ***************************************************

Programme qui contient les fonctions nécessaires pour calculer le score

*************************************************** */

int Somme(Partie partie){
    Case **plateau = partie.entrepot;
    int somme = 0;
    for (int i = 1; i < NB_LIGNE - 1; i++) {
        for (int j = 1; j < NB_LIGNE - 1; j++) {
            if (plateau[j][i].e == boite){
                somme += 100 * j + i;
                }
            }
        }
    return somme;
}
