#include "declaration.h"

/**
 * @file main.c
 * @brief Point d'entrée principal du programme "Les malheurs de l'entrepôt".
 */

/**
 * @brief Structure globale représentant la partie en cours.
 */
Partie partie;

/**
 * @brief Variable globale utilisée pour interagir avec les menus et les commandes clavier.
 */
char echap;





/**
 * @brief Fonction principale du programme.
 * 
 * Permet à l'utilisateur de choisir le mode d'affichage (terminal ou SDL) et le type de commande (fichier ou clavier).
 * 
 * @return int Code de retour du programme (0 si succès).
 */
int main() {

    Partie partie;
    partie.largeur = 8;
    partie.hauteur = 8;
    
    printf("Les malheurs de l'entrepôt :\n");
    printf("Quel affichage de l'entrepôt ?\n"
           " taper 'o' pour l'entrepôt sur le terminal avec le fichier commande pour les déplacements,\n"
           " taper 't' pour l'entrepôt sur le terminal avec le fichier commande pour les déplacements et l'initialisation de l'entrepôt,\n"
           " taper 'u' pour l'entrepôt sur le terminal avec le déplacement du robot zqsd,\n"
           " taper 'm' pour l'entrepôt sur le terminal avec le fichier commande pour les déplacements et l'initialisation de l'entrepôt élargie,\n"
           " taper 'l' pour l'entrepôt sur le terminal avec le fichier commande pour l'initialisation de l'entrepôt élargie et le déplacement du robot zqsd,\n"
           " taper 'y' pour l'entrepôt sur la fenêtre de graphique avec le fichier commande pour les déplacements,\n"
           " taper 'i' pour l'entrepôt sur la fenêtre de graphique avec le déplacement du robot zqsd,\n"
           " sélectionner 'p' pour sortir.\n");

    scanf(" %c", &echap);

    if (echap == 'o') {
        partie.entrepot = creer_entrepot(&partie);
        fichier_commandes("Commande_Du_Robot.txt", &partie);
        afficher_entrepot(&partie);
    }
    
    if (echap == 't') {
        determiner_dimensions("commandeProf2.txt", &partie);
        partie.entrepot = cree_et_initialisation_fichier("commandeProf2.txt", &partie);
        afficher_entrepot(&partie);
        fichier_commandes("commandeProf2.txt", &partie);
        afficher_entrepot(&partie);
    }

    if (echap == 'u') {
        partie.entrepot = creer_entrepot(&partie);
        while (echap != 'p') {
            afficher_entrepot(&partie);
            deplacement(&partie, &echap);
        }
        echap = 'u';
    }

    if (echap == 'i') {
        partie.entrepot = creer_entrepot(&partie);
        affichage(&partie);
    }

    if (echap == 'y') {
        partie.entrepot = creer_entrepot(&partie);
        SDL2_fichier_commandes("Commande_Du_Robot.txt", &partie);
    }
    
    if (echap == 'm') {
    
        // on affiche l'entrepôt non élargie
        printf("Entrepôt initial : \n");
        determiner_dimensions("commandeProf2.txt", &partie);
        partie.entrepot = cree_et_initialisation_fichier("commandeProf2.txt", &partie);
        afficher_entrepot(&partie);
        liberer_entrepot(partie);
        
        // on utilise le fichier pour créé l'entrepôt élargie et le modifier
        partie.entrepot = cree_et_initialisation_fichier_elargie("commandeProf2.txt", &partie);
        printf("Entrepôt élargie : \n");
        afficher_entrepot(&partie);
        fichier_commandes_elargie("commandeProf2.txt", &partie);
        printf("Entrepôt élargie après déplacement : \n");
        afficher_entrepot(&partie);
    }
    
    if (echap == 'l') {
    
        // on affiche l'entrepôt non élargie
        printf("Entrepôt initial : \n");
        determiner_dimensions("commandeProf2.txt", &partie);
        partie.entrepot = cree_et_initialisation_fichier("commandeProf2.txt", &partie);
        printf("partie->largeur : %d, partie->hauteur : %d\n",partie.largeur,partie.hauteur);
        afficher_entrepot(&partie);
        liberer_entrepot(partie);
        
        // on utilise le fichier pour créé l'entrepôt élargie et le modifier
        partie.entrepot = cree_et_initialisation_fichier_elargie("commandeProf2.txt", &partie);
        printf("partie->largeur : %d, partie->hauteur : %d\n",partie.largeur,partie.hauteur);
        printf("Entrepôt élargie : \n");
        while (echap != 'p') {
            afficher_entrepot(&partie);
            deplacement_elargie(&partie, &echap);
            printf(" 'p' pour quitter le mode \n");
        }
        echap = 'l';
        printf("Entrepôt élargie après déplacement : \n");
        afficher_entrepot(&partie);
    }

    if (echap == 'u' || echap == 'o' || echap == 'i' || echap == 'y' || echap == 't' || echap == 'm' || echap == 'l') {
        printf("Somme des coordonnées GPS de toutes les boîtes : %d\n", Somme(partie));
        liberer_entrepot(partie);
    }

    return 0;
}

