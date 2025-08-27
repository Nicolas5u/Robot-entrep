#ifndef DECLARATION_H
#define DECLARATION_H

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

/**
 * @enum Element
 * @brief Représente le type d'élément présent dans une case de l'entrepôt
 */
typedef enum { 
    vide,       /**< Case vide */
    robot,      /**< Position du robot de travail */
    mur,        /**< Mur indéplaçable */
    boite,      /**< Boîte */
    caseDeChemin, /**< Chemin */
    boiteG,     /**< Partie gauche d'une boîte élargie */
    boiteD      /**< Partie droite d'une boîte élargie */
} Element;

/**
 * @struct Case
 * @brief Représente une case de l'entrepôt
 */
typedef struct {
    Element e; /**< Élément contenu dans la case */
} Case;

/**
 * @struct Coup
 * @brief Représente un mouvement ou une action du robot
 */
typedef struct {
    int xFrom;    /**< Position x de départ */
    int yFrom;    /**< Position y de départ */
    int last_x;   /**< Dernière position x */
    int last_y;   /**< Dernière position y */
    int start_x;  /**< Position x initiale */
    int start_y;  /**< Position y initiale */
    int fin;      /**< Indique si le coup est terminé */
    int compt;    /**< Compteur associé au coup */
} Coup;

/**
 * @struct Noeud
 * @brief Maillon d'une liste chaînée
 */
typedef struct Noeud {
    Coup pos;             /**< Coup enregistré */
    struct Noeud* suivant; /**< Pointeur vers le prochain noeud */
} Noeud;

/**
 * @struct Liste
 * @brief Représente une liste chaînée
 */
typedef struct {
    Noeud* tete; /**< Premier élément de la liste */
    Noeud* queue; /**< Dernier élément de la liste */
} Liste;

/**
 * @struct Partie
 * @brief Représente l'état complet d'une partie
 */
typedef struct {
    Case** entrepot; /**< Plateau de jeu représentant l'entrepôt */
    Coup coup;       /**< Dernier coup joué */
    int largeur;     /**< Largeur de l'entrepôt */
    int hauteur;     /**< Hauteur de l'entrepôt */
    Liste l;         /**< Liste */
} Partie;

/* Définitions de toutes les fonctions */

/**
 * @brief Retourne la couleur associée à un élément
 */
char* couleur_element(Element e);

/**
 * @brief Crée et initialise un entrepôt simple
 */
Case** creer_entrepot(Partie* partie);

/**
 * @brief Libère la mémoire d'un entrepôt en fonction de sa taille
 */
void liberer_entrepot(Partie partie);

/**
 * @brief Affiche l'entrepôt sur le terminal
 */
void afficher_entrepot(Partie* partie);

/**
 * @brief Place les éléments initiaux dans l'entrepôt
 */
void PlacementInitiale(Case** entrepot, Partie* partie);

/**
 * @brief Déplace le robot avec une interaction de l'utilisateur
 */
void deplacement(Partie* partie, char* echap);

/**
 * @brief Déplace le robot vers la droite
 */
void deplacement_D(Partie* partie);

/**
 * @brief Déplace le robot vers la gauche
 */
void deplacement_G(Partie* partie);

/**
 * @brief Déplace le robot vers le bas
 */
void deplacement_B(Partie* partie);

/**
 * @brief Déplace le robot vers le haut
 */
void deplacement_H(Partie* partie);

/**
 * @brief Calcule la somme des coordonnées GPS des boîtes pour l'entrepôt élargie et simple
 */
int Somme(Partie partie);

/**
 * @brief Affiche l'entrepôt avec SDL2
 */
int affichage(Partie* partie);

/**
 * @brief Charge et exécute des commandes depuis un fichier avec SDL2
 */
int SDL2_fichier_commandes(const char* Commande_Du_Robot, Partie* partie);

/**
 * @brief Affiche l'entrepôt avec SDL2
 */
void SDL2_Affiche_entrepot(SDL_Renderer* renderer,Partie* partie);

/**
 * @brief Charge des commandes avec un fichier texte
 */
void fichier_commandes(const char* Commande_Du_Robot, Partie* partie);

/**
 * @brief Charge des commandes avec un fichier texte pour de l'élargie
 */
void fichier_commandes_elargie(const char* Commande_Du_Robot, Partie* partie);

/**
 * @brief Détermine les dimensions de l'entrepôt
 */
void determiner_dimensions(const char* commandeProf,Partie* partie);

/**
 * @brief Crée et initialise un entrepôt à partir d'un fichier
 */
Case** cree_et_initialisation_fichier(const char* Commande_Du_Robot, Partie* partie);

/**
 * @brief Crée et initialise un entrepôt à partir d'un fichier pour de l'élargie
 */
Case** cree_et_initialisation_fichier_elargie(const char* commandeProf, Partie* partie);

/**
 * @brief Déplace le robot dans un entrepôt élargie
 */
void deplacement_elargie(Partie* partie, char* echap);

/**
 * @brief Déplace le robot vers la droite dans un entrepôt élargie
 */
void deplacement_D_elargie(Partie* partie);

/**
 * @brief Déplace le robot vers la gauche dans un entrepôt élargie
 */
void deplacement_G_elargie(Partie* partie);

/**
 * @brief Déplace le robot vers le bas dans un entrepôt élargie
 */
void deplacement_B_elargie(Partie* partie);

/**
 * @brief Fonction récursive pour le déplacement vers le bas dans un entrepôt élargie
 */
void R_deplacement_B_elargie(Partie* partie, Liste*, Case** lenregistrement_plateau);

/**
 * @brief Affiche l'entrepôt après un déplacement bas dans un entrepôt élargie
 */
void deplacement_B_elargie_affichage(Partie* partie);

/**
 * @brief Vérifie si un déplacement bas est possible dans un entrepôt élargie
 */
int deplacement_bas_possible(Partie* partie);

/**
 * @brief Libère la mémoire d'un entrepôt enregistré
 */
void liberer_entrepot_enregistre(Case** plateau, int hauteur);

/**
 * @brief Crée une copie un entrepôt
 */
Case** copier_plateau(Case** original, int hauteur, int largeur);

/**
 * @brief Déplace le robot vers le haut dans un entrepôt élargie
 */
void deplacement_H_elargie(Partie* partie);

/**
 * @brief Fonction récursive pour le déplacement vers le haut dans un entrepôt élargie
 */
void R_deplacement_H_elargie(Partie* partie, Liste*, Case** lenregistrement_plateau);

/**
 * @brief Affiche l'entrepôt après un déplacement haut dans un entrepôt élargie
 */
void deplacement_H_elargie_affichage(Partie* partie);

/**
 * @brief Vérifie si un déplacement haut est possible dans un entrepôt élargie
 */
int deplacement_haut_possible(Partie* partie);

/**
 * @brief Crée une nouvelle liste
 */
Liste* creer_liste();

/**
 * @brief Ajoute un coup à une liste
 */
void ajouter_coup(Liste* l, int x, int y);

/**
 * @brief Vérifie si une liste est vide
 */
int liste_vide(Liste* l);

/**
 * @brief Retire un coup d'une liste
 */
int retirer_coup(Liste* l, Partie* partie);

/**
 * @brief Affiche le contenu d'une liste
 */
void afficher_liste(Liste* l);

/**
 * @brief Libère la mémoire associée à une liste
 */
void liberer_liste(Liste* l);

#endif

