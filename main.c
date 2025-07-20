#include "declaration.h"
Partie partie;
char echap;

int main() {
        printf("Les malheurs de l'entrepôt\n");
        printf("Dans quel entrepôt le robot pose t'il des problèmes ? (taper 'o' pour l'entrepôt prédéfini, l'autre version n'est pas encore disponible");
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
    
	liberer_entrepot(partie);
	return 0;
}
