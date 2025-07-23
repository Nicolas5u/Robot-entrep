#include "declaration.h"
Partie partie;
char echap;

int main() {
        printf("Les malheurs de l'entrepôt\n");
        printf("Dans quel entrepôt le robot pose t'il des problèmes ?\n(taper 'o' pour le petit entrepôt prédéfini,\n taper 'i' pour le plus grand entrepôt");
        scanf(" %c",&echap);
        Initianise_entrepot(&partie, echap);
        
        int mode;
        printf("Utiliser fichier commande ? (oui : 1, non : 2)");
        scanf(" %d", &mode);
        if(mode == 1){
            fichier_commandes("Commande_Du_Robot.txt", &partie);
        }else{
            while (echap != 'p'){
                afficher_entrepot(&partie);
                deplacement(&partie, &echap);
            }
        }
        printf("Somme des coordonnées GPS de toutes les boîtes : %d\n", Somme(partie));
	liberer_entrepot(partie);
	return 0;
}
