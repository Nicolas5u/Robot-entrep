#include "declaration.h"

/**
 * @file main.c
 * @brief Point d'entrée principal du programme "Les malheurs de l'entrepôt"
 */

/**
 * @brief Structure globale représentant la partie
 */
Partie partie;

char echap;

/**
 * @brief Fonction principale du programme
 * 
 * - o : Affichage terminal avec fichier de commandes 
 * - t : Affichage terminal avec initialisation et commandes via fichier
 * - u : Affichage terminal avec déplacements clavier (zqsd)
 * - m : Mode élargi avec fichier pour initialisation + commandes
 * - l : Mode élargi avec fichier pour initialisation + déplacements clavier (zqsd)
 * - y : Affichage graphique SDL avec fichier de commandes
 * - i : Affichage graphique SDL avec déplacements clavier
 * - p : Quitter le programme
 * 
 * @return int Code de retour du programme 0 en cas de succès
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
        determiner_dimensions("commandeProf.txt", &partie);
        partie.entrepot = cree_et_initialisation_fichier("commandeProf.txt", &partie);
        afficher_entrepot(&partie);
        fichier_commandes("commandeProf.txt", &partie);
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
        determiner_dimensions("commandeProf.txt", &partie);
        printf(" %d, %d ",partie.hauteur,partie.largeur);
        partie.entrepot = cree_et_initialisation_fichier("commandeProf.txt", &partie);
        afficher_entrepot(&partie);
        liberer_entrepot(partie);
        
        // on utilise le fichier pour créé l'entrepôt élargie et le modifier
        partie.entrepot = cree_et_initialisation_fichier_elargie("commandeProf.txt", &partie);
        printf("Entrepôt élargie : \n");
        afficher_entrepot(&partie);
        fichier_commandes_elargie("commandeProf.txt", &partie);
        printf("Entrepôt élargie après déplacement : \n");
        afficher_entrepot(&partie);
    }
    
    if (echap == 'l') {
    
        // on affiche l'entrepôt non élargie
        printf("Entrepôt initial : \n");
        determiner_dimensions("commandeProf2.txt", &partie);
        partie.entrepot = cree_et_initialisation_fichier("commandeProf2.txt", &partie);
        afficher_entrepot(&partie);
        liberer_entrepot(partie);
        
        // on utilise le fichier pour créé l'entrepôt élargie et le modifier
        partie.entrepot = cree_et_initialisation_fichier_elargie("commandeProf2.txt", &partie);
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
    

    if (echap == 'u' || echap == 'o' || echap == 'i' || echap == 'y' || echap == 't' || echap == 'm' || echap == 'l' || echap == 'i') {
        printf("Somme des coordonnées GPS de toutes les boîtes : %d\n", Somme(partie));
        liberer_entrepot(partie);
    }

    return 0;
}

