#include "declaration.h"
Partie partie;
char echap;

int main() {
        printf("Les malheurs de l'entrepôt\n");
        printf("Dans quel entrepôt le robot pose t'il des problèmes ? (taper 1 pour l'entrepôt prédéfini, l'autre version n'est pas encore disponible");
        scanf(" %c",&echap);
        Initianise_entrepot(&partie, echap);
        
        while (echap != 'p'){
            afficher_entrepot(&partie);
            deplacement(&partie, &echap);
        }
    
	liberer_entrepot(partie);
	return 0;
}
