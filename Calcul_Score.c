#include "declaration.h"

/**
 * @file score.c
 * @brief Contient les fonctions nécessaires pour calculer le score du jeu.
 */

/**
 * @brief Calcule la somme des scores en fonction des positions des boîtes.
 * 
 * Le score est déterminé en ajoutant `100 * ligne + colonne` pour chaque boîte.
 * 
 * @param partie La structure Partie contenant l'entrepôt.
 * @return La somme calculée comme score.
 */
int Somme(Partie partie){

    Case **plateau = partie.entrepot;
    int somme = 0;
    for (int i = 1; i < partie.largeur - 1; i++) {
        for (int j = 1; j < partie.hauteur - 1; j++) {
            if (plateau[j][i].e == boite){
                somme += 100 * j + i;
            }
        }
    }
    return somme;
}

