#include "declaration.h"

/**
 * @brief Lit les commandes depuis un fichier et exécute les déplacements correspondants.
 * 
 * @param Commande_Du_Robot Chemin vers le fichier de commandes.
 * @param partie Pointeur vers la structure de la partie.
 */


void fichier_commandes(const char* Commande_Du_Robot, Partie* partie){

    FILE* fichier = fopen(Commande_Du_Robot, "r");
    if (fichier == NULL) {
        printf("Erreur à l'ouverture du fichier %s\n", Commande_Du_Robot);
        return;
    }

    char commande;
    while ((commande = fgetc(fichier)) != EOF) {
        switch (commande) {
            case 'z':
            case '^': deplacement_H(partie); break;
            case 's':
            case 'v': deplacement_B(partie); break;
            case 'q':
            case '<': deplacement_G(partie); break;
            case 'd':
            case '>': deplacement_D(partie); break;
            case ' ':
            case '\n':
            case '\r': break;
            default:
                // printf("Commande inconnue : %c\n", commande);
                break;
        }
    }

    if (fclose(fichier) != 0) {
        printf("Erreur à la fermeture du fichier.\n");
    }
}

void fichier_commandes_elargie(const char* Commande_Du_Robot, Partie* partie){

    FILE* fichier = fopen(Commande_Du_Robot, "r");
    if (fichier == NULL) {
        printf("Erreur à l'ouverture du fichier %s\n", Commande_Du_Robot);
        return;
    }

    char commande;
    while ((commande = fgetc(fichier)) != EOF) {
        switch (commande) {
            case 'z':
            case '^': deplacement_H_elargie(partie); break;
            case 's':
            case 'v': deplacement_B_elargie(partie); break;
            case 'q':
            case '<': deplacement_G_elargie(partie); break;
            case 'd':
            case '>': deplacement_D_elargie(partie); break;
            case ' ':
            case '\n':
            case '\r': break;
            default:
                // printf("Commande inconnue : %c\n", commande);
                break;
        }
    }

    if (fclose(fichier) != 0) {
        printf("Erreur à la fermeture du fichier.\n");
    }
}

void determiner_dimensions(const char* commandeProf,Partie* partie) {
    FILE* fichier = fopen(commandeProf, "r");
    if (fichier == NULL) {
        printf("Erreur à l'ouverture du fichier %s\n", commandeProf);
        return;
    }

    char ligne[1024];
    int LARGEUR = 0;
    int HAUTEUR = 0;

    // Calcul de la largeur
    if (fgets(ligne, sizeof(ligne), fichier)) {
        LARGEUR = strcspn(ligne, "\r\n");
        HAUTEUR = 1;
    }

    rewind(fichier);

    // ignore la première ligne
    if (!fgets(ligne, sizeof(ligne), fichier)) {
        return;
    }
    
    while (fgets(ligne, sizeof(ligne), fichier)) {
        // enlever le retour à la ligne
        int len = strcspn(ligne, "\r\n");
        ligne[len] = '\0';

        // vérifier si la ligne est composée uniquement de mur
        int i = 0;
        int seulement_mur = 1;
        while (ligne[i] != '\0') {
            if (ligne[i] != '#') {
                seulement_mur = 0;
                break;
            }
            i++;
        }

        if (seulement_mur) {
            break;
        } else {
            HAUTEUR++;
        }
    }
    HAUTEUR++;
    fclose(fichier);

    partie->hauteur = HAUTEUR;
    partie->largeur = LARGEUR;
}


Case** cree_et_initialisation_fichier(const char* commandeProf, Partie* partie) {

    FILE* fichier = fopen(commandeProf, "r");
    if (fichier == NULL) {
        printf("Erreur à l'ouverture du fichier %s\n", commandeProf);
        return NULL;
    }

    // Allocation du tableau 2D de Case
    Case** entrepot = malloc(partie->hauteur * sizeof(Case*));
    if (entrepot == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        fclose(fichier);
        return NULL;
    }

    for (int i = 0; i < partie->hauteur; i++) {
        entrepot[i] = malloc(partie->largeur * sizeof(Case));
        if (entrepot[i] == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire\n");
            for (int j = 0; j < i; j++) {
                free(entrepot[j]);
            }
            free(entrepot);
            fclose(fichier);
            return NULL;
        }
    }

    // initialisation de l'entrepôt
    char ligne[512];
    int y = 0;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL && y < partie->hauteur) {
        for (int x = 0; x < partie->largeur && ligne[x] != '\0' && ligne[x] != '\n'; x++) {
            switch (ligne[x]) {
                case '#':
                    entrepot[y][x].e = mur;
                    break;
                case 'O':
                    entrepot[y][x].e = boite;
                    break;
                case '@':
                    entrepot[y][x].e = robot;
                    partie->coup.xFrom = x;
                    partie->coup.yFrom = y;
                    break;
                case '.':
                    entrepot[y][x].e = caseDeChemin;
                    break;
                default:
                    entrepot[y][x].e = vide;
                    break;
            }
        }
        y++;
    }

    fclose(fichier);
    return entrepot;
}

Case** cree_et_initialisation_fichier_elargie(const char* commandeProf, Partie* partie) {
    
    FILE* fichier = fopen(commandeProf, "r");
    if (fichier == NULL) {
        printf("Erreur à l'ouverture du fichier %s\n", commandeProf);
        return NULL;
    }

    // Allocation du tableau 2D de Case
    Case** entrepot = malloc(partie->hauteur * sizeof(Case*));
    if (entrepot == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        fclose(fichier);
        return NULL;
    }

    for (int i = 0; i < partie->hauteur; i++) {
        entrepot[i] = malloc(partie->largeur * 2 * sizeof(Case));
        if (entrepot[i] == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire\n");
            for (int j = 0; j < i; j++) {
                free(entrepot[j]);
            }
            free(entrepot);
            fclose(fichier);
            return NULL;
        }
    }

    // initialisation de l'entrepôt
    char ligne[partie->largeur * 2 + 2];
    int y = 0;
    // printf("on dans crée_et_initialisation_fichier_élargie du fichier commande %d\n",partie->largeur);
    while (fgets(ligne, sizeof(ligne), fichier) != NULL && y < partie->hauteur) {
        for (int x = 0; x < partie->largeur && ligne[x] != '\0' && ligne[x] != '\n'; x++) {
            switch (ligne[x]) {
                case '#':
                    entrepot[y][x * 2].e = mur;
                    entrepot[y][x * 2 + 1].e = mur;
                    break;
                case 'O':
                    entrepot[y][x * 2].e = boiteG;
                    entrepot[y][x * 2 + 1].e = boiteD;
                    break;
                case '@':
                    entrepot[y][x * 2].e = robot;
                    entrepot[y][x * 2 + 1].e = caseDeChemin;
                    partie->coup.xFrom = x * 2;
                    partie->coup.yFrom = y;
                    break;
                case '.':
                    entrepot[y][x * 2].e = caseDeChemin;
                    entrepot[y][x * 2 + 1].e = caseDeChemin;
                    break;
                default:
                    entrepot[y][x * 2].e = vide;
                    entrepot[y][x * 2 + 1].e = vide;
                    break;
            }
        }
        y++;
    }
    partie->largeur = partie->largeur * 2;
    fclose(fichier);
    return entrepot;
}

