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
    int tailleC = 8;
    int tailleL = 8;
    partie.largeur = tailleC;
    partie.hauteur = tailleL;
    
    printf("Les malheurs de l'entrepôt :\n");
    printf("Quel affichage de l'entrepôt ?\n"
           " taper 'o' pour l'entrepôt sur le terminal avec le fichier commande pour les déplacements,\n"
           " taper 't' pour l'entrepôt sur le terminal avec le fichier commande pour les déplacements et l'initialisation de l'entrepôt,\n"
           " taper 'u' pour l'entrepôt sur le terminal avec le déplacement du robot zqsd,\n"
           " taper 'm' pour l'entrepôt sur le terminal avec le fichier commande pour les déplacements et l'initialisation de l'entrepôt élargie,\n"
           " taper 'y' pour l'entrepôt sur la fenêtre de graphique avec le fichier commande pour les déplacements,\n"
           " taper 'i' pour l'entrepôt sur la fenêtre de graphique avec le déplacement du robot zqsd,\n"
           " sélectionner 'p' pour sortir.\n");

    scanf(" %c", &echap);

    if (echap == 'o') {
        partie.entrepot = creer_entrepot(&partie,tailleC,tailleL);
        fichier_commandes("Commande_Du_Robot.txt", &partie, tailleL, tailleC);
        afficher_entrepot(&partie);
    }
    
    if (echap == 't') {
        determiner_dimensions("commandeProf2.txt", &partie);
        partie.entrepot = cree_et_initialisation_fichier("commandeProf2.txt", &partie);
        afficher_entrepot(&partie);
        fichier_commandes("commandeProf2.txt", &partie, partie.largeur, partie.hauteur);
        afficher_entrepot(&partie);
    }

    if (echap == 'u') {
        partie.entrepot = creer_entrepot(&partie,tailleC,tailleL);
        while (echap != 'p') {
            afficher_entrepot(&partie);
            deplacement(&partie, &echap, tailleL, tailleC);
        }
        echap = 'u';
    }

    if (echap == 'i') {
        partie.entrepot = creer_entrepot(&partie,tailleC,tailleL);
        affichage(&partie,tailleL,tailleC);
    }

    if (echap == 'y') {
        partie.entrepot = creer_entrepot(&partie,tailleC,tailleL);
        SDL2_fichier_commandes("Commande_Du_Robot.txt", &partie,tailleL, tailleC);
    }
    
    if (echap == 'm') {
        determiner_dimensions("commandeProf2.txt", &partie);
        printf("on à déterminé les dimensions du fichier commande %d\n",partie.hauteur);
        partie.entrepot = cree_et_initialisation_fichier_elargie("commandeProf2.txt", &partie);
        printf("on à crée_et_initialisation_fichier_élargie du fichier commande %d\n",partie.hauteur);
        afficher_entrepot(&partie);
        printf("on à affiché l'entrepôt %d\n",partie.hauteur);
        fichier_commandes_elargie("commandeProf2.txt", &partie, partie.largeur, partie.hauteur);
        afficher_entrepot(&partie);
    }

    if (echap == 'u' || echap == 'o' || echap == 'i' || echap == 'y' || echap == 't' || echap == 'm') {
        printf("Somme des coordonnées GPS de toutes les boîtes : %d\n", Somme(partie));
        liberer_entrepot(partie,tailleL);
    }

    return 0;
}

