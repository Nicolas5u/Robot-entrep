#include "declaration.h"
Partie partie;
int Qentrepot;

int main() {
        printf("Les malheurs de l'entrepôt\n");
        printf("Dans quel entrepôt le robot pose t'il des problèmes ? (taper 1 pour l'entrepôt prédéfini, l'autre version n'est pas encore disponible");
        scanf("%d",&Qentrepot);
        Initianise_entrepot(&partie, Qentrepot);
        
        afficher_entrepot(&partie);
    
	liberer_entrepot(partie);
	return 0;
}
