#include "declaration.h"

// Créer une liste vide
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

// Ajouter un coup à la fin
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

// Vérifie si la liste est vide
int liste_vide(Liste* l) {
    return l->tete == NULL;
}

// Retirer et récupérer le premier coup
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



// Afficher toute la liste
void afficher_liste(Liste* l) {
    Noeud* courant = l->tete;
    printf("Liste des coups :\n");
    while (courant != NULL) {
        printf(" -> (%d, %d)\n", courant->pos.xFrom, courant->pos.yFrom);
        courant = courant->suivant;
    }
}

// Libérer toute la liste
void liberer_liste(Liste* l) {
    Noeud* courant = l->tete;
    while (courant != NULL) {
        Noeud* tmp = courant;
        courant = courant->suivant;
        free(tmp);
    }
    free(l);
}
