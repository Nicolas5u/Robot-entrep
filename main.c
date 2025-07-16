#include "declaration.h"
Partie partie;
int Qentrepot;
int echap;

int main() {
        printf("Les malheurs de l'entrepôt\n");
        printf("Dans quel entrepôt le robot pose t'il des problèmes ? (taper 1 pour l'entrepôt prédéfini, l'autre version n'est pas encore disponible");
        scanf("%d",&Qentrepot);
        Initianise_entrepot(&partie, Qentrepot);
        
        while (echap != 27 || Qentrepot != 27){
            afficher_entrepot(&partie);
            deplacement(&partie);
            scanf("%d",&echap);
        }
    
	liberer_entrepot(partie);
	return 0;
}
