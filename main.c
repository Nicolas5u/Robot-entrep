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
    printf("Les malheurs de l'entrepôt :\n");
    printf("Quel affichage de l'entrepôt ?\n"
           " taper 'o' pour l'entrepôt sur le terminal avec le fichier commande,\n"
           " taper 'u' pour l'entrepôt sur le terminal avec le déplacement du robot zqsd,\n"
           " taper 'y' pour l'entrepôt sur la fenêtre de graphique avec le fichier commande,\n"
           " taper 'i' pour l'entrepôt sur la fenêtre de graphique avec le déplacement du robot zqsd,\n"
           " sélectionner 'p' pour sortir.\n");

    scanf(" %c", &echap);

    if (echap == 'o') {
        partie.entrepot = creer_entrepot(&partie);
        fichier_commandes("Commande_Du_Robot.txt", &partie);
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

    if (echap == 'u' || echap == 'o' || echap == 'i' || echap == 'y') {
        printf("Somme des coordonnées GPS de toutes les boîtes : %d\n", Somme(partie));
        liberer_entrepot(partie);
    }

    return 0;
}

