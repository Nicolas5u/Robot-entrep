#include "declaration.h"

/**
 * @file liste.c
 * @brief Gestion des listes chaînées (pour mémoriser les coups lors des déplacements)
 *
 * Ce fichier contient l’implémentation des fonctions permettant de créer, manipuler et
 * libérer une liste chaînée utilisée pour stocker des coups (positions intermédiaires)
 */

/**
 * @brief Crée une liste chaînée vide
 *
 * Alloue dynamiquement une structure Liste et initialise ses pointeurs à NULL
 * En cas d’échec d’allocation, le programme s’arrête avec EXIT_FAILURE
 *
 * @return Pointeur vers la liste nouvellement créée.
 */
Liste* creer_liste() {
    Liste* l = malloc(sizeof(Liste));
    if (!l) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    l->tete = NULL;
    l->queue = NULL;
    return l;
}

/**
 * @brief Ajoute une position du robot non vérifié (x,y) à la fin de la liste
 *
 * Alloue un nouveau noeud contenant la position et l’ajoute en queue de la liste
 *
 * @param l Pointeur vers la liste
 * @param x Coordonnée
 * @param y Coordonnée
 */
void ajouter_coup(Liste* l, int x, int y) {
    Noeud* nouveau = malloc(sizeof(Noeud));
    if (!nouveau) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    nouveau->pos.xFrom = x;
    nouveau->pos.yFrom = y;
    nouveau->pos.last_x = 0;
    nouveau->pos.last_y = 0;
    nouveau->pos.compt = 0;
    nouveau->suivant = NULL;

    if (l->queue == NULL) { // Liste vide
        l->tete = nouveau;
        l->queue = nouveau;
    } else {
        l->queue->suivant = nouveau;
        l->queue = nouveau;
    }
}

/**
 * @brief Vérifie si la liste est vide
 *
 * @param l Pointeur vers la liste
 * @return 1 si la liste est vide, 0 sinon
 */
int liste_vide(Liste* l) {
    return l->tete == NULL;
}

/**
 * @brief Retire et récupère le premier coup de la liste
 *
 * Le premier noeud est supprimé et ses coordonnées sont copiées
 *
 * @param l Pointeur vers la liste
 * @param partie Pointeur vers la partie, dont la structure Coup est mise à jour
 * @return 1 si un coup a été retiré avec succès, 0 si la liste était vide
 */
int retirer_coup(Liste* l, Partie* partie) {
    if (liste_vide(l)) return 0;  // rien à retirer

    Noeud* tmp = l->tete;

    // Mise à jour directe de partie->coup
    partie->coup.xFrom = tmp->pos.xFrom;
    partie->coup.yFrom = tmp->pos.yFrom;

    l->tete = tmp->suivant;
    if (l->tete == NULL) {
        l->queue = NULL; // liste vide
    }

    free(tmp);
    return 1; // succès
}

/**
 * @brief Affiche le contenu de la liste
 *
 * Parcourt la liste et affiche chaque couple de coordonnées (utilisé pour la résolution des problème du code)
 *
 * @param l Pointeur vers la liste
 */
void afficher_liste(Liste* l) {
    Noeud* courant = l->tete;
    printf("Liste des coups :\n");
    while (courant != NULL) {
        printf(" -> (%d, %d)\n", courant->pos.xFrom, courant->pos.yFrom);
        courant = courant->suivant;
    }
}

/**
 * @brief Libère toute la mémoire occupée par la liste
 *
 * Parcourt la liste, libère chaque noeud, puis libère la structure Liste elle-même
 *
 * @param l Pointeur vers la liste à détruire
 */
void liberer_liste(Liste* l) {
    Noeud* courant = l->tete;
    while (courant != NULL) {
        Noeud* tmp = courant;
        courant = courant->suivant;
        free(tmp);
    }
    free(l);
}

