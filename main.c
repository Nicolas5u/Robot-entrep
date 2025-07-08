#include "declaration.h"

int main() {
        printf("Les malheurs de l'entrepôt\n");
        Partie partie;
        partie.entrepot = creer_plateau();
        afficher_entrepot(&partie);
    
	liberer_plateau(partie);
	return 0;
}
