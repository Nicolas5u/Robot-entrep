#include "declaration.h"
Partie partie;
char echap;

int main() {
        printf("Les malheurs de l'entrepôt :\n");
        printf("Quel affichage de l'entrepôt ?\n taper 'o' pour l'entrepôt sur le terminal avec le fichier commande,\n taper 'u' pour l'entrepôt sur le terminal avec le déplacement du robot zqsd,\n taper 'i' pour la fenêtre d'affichage graphique,\n selectionner 'p' pour sortir.\n");
        scanf(" %c",&echap);
        
        if (echap == 'o'){
            partie.entrepot = creer_entrepot(echap, &partie);
            fichier_commandes("Commande_Du_Robot.txt", &partie);
        }
        if (echap == 'u'){
            partie.entrepot = creer_entrepot(echap, &partie);
            while (echap != 'p'){
                afficher_entrepot(&partie);
                deplacement(&partie, &echap);
            }
            echap = 'u';
        }
        if (echap == 'u' ||echap == 'o'){
            printf("Somme des coordonnées GPS de toutes les boîtes : %d\n", Somme(partie));
            liberer_entrepot(partie);
        }
        if (echap == 'i'){
            affichage();
        }
        
        
	return 0;
}
