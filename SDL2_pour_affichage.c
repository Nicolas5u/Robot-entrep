#include "declaration.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int CELL_SIZE = 60;

int affichage(Partie* partie) {

// Début de l'initialisation de la fenêtre graphique  
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur SDL : %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Les malheurs de l'entrepôt",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Erreur fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erreur renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
// Fin de l'initialisation de la fenêtre graphique 

// Gestion des événements clavier avec boucle de sorti
    int quit = 0;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDL_QUIT:
                        quit = 1;
                        break;
                    case SDLK_ESCAPE:
                        quit = 1;
                        break;
                    case SDLK_z:
                        deplacement_H(partie);
                        break;
                    case SDLK_s:
                        deplacement_B(partie);
                        break;
                    case SDLK_q:
                        deplacement_G(partie);
                        break;
                    case SDLK_d:
                        deplacement_D(partie);
                        break;
                }
            }
        }

        // Affiche l'entrepôt
        SDL2_Affiche_entrepot(renderer,partie);

        // On affiche le résultat à l'écran
        SDL_RenderPresent(renderer);
        
        // Délai entre chaque commande (en mettant 16 on a 60 images par seconde)
        SDL_Delay(16);
        
    }

    // On ferme proprement l'interface
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

// Fonction qui permet d'utiliser le ficher commande en txt

int SDL2_fichier_commandes(const char* Commande_Du_Robot, Partie* partie) {

// Début de l'initialisation de la fenêtre graphique
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur SDL : %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Les malheurs de l'entrepôt",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Erreur fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erreur renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
// Fin de l'initialisation de la fenêtre graphique 

// Début du copier coller de la fonction fichier_commandes
    FILE* fichier = fopen(Commande_Du_Robot, "r");
    if (!fichier) {
        printf("Erreur à l'ouverture du fichier %s\n", Commande_Du_Robot);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    char commande;
    while ((commande = fgetc(fichier)) != EOF) {
        switch (commande) {
            case 'z':
            case '^': deplacement_H(partie); break;
            case 's':
            case 'v': deplacement_B(partie); break;
            case 'q':
            case '<': deplacement_G(partie); break;
            case 'd':
            case '>': deplacement_D(partie); break;
            case ' ':
            case '\n':
            case '\r': 
                break; // ignorer les blancs et sauts de ligne
                
            default:
                printf("Commande inconnue : %c\n", commande);
                break;
        }
// Fin du copier coller de la fonction fichier_commandes

        // Affiche l'entrepôt
        SDL2_Affiche_entrepot(renderer,partie);

        // On affiche le résultat à l'écran
        SDL_RenderPresent(renderer);
        
        // Délai entre chaque commande
        SDL_Delay(300);
    }
    
// On ferme proprement l'interface
    fclose(fichier);
    SDL_Delay(1000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void SDL2_Affiche_entrepot(SDL_Renderer* renderer,Partie* partie){
    
    
    // Efface l'écran pour ne pas avoir des fenêtres qui s'accumulent
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

    for (int row = 0; row < NB_LIGNE; row++) {
            for (int col = 0; col < NB_LIGNE; col++) {
                SDL_Rect cell = {
                    col * CELL_SIZE,
                    row * CELL_SIZE,
                    CELL_SIZE,
                    CELL_SIZE
                };

                switch (partie->entrepot[row][col].e) {
                    case mur:
                        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255); // gris foncé
                        break;
                    case robot:
                        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // rouge
                        break;
                    case boite:
                        SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255); // marron
                        break;
                    case caseDeChemin:
                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // blanc
                        break;
                    default:
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // noir
                        break;
                }

                SDL_RenderFillRect(renderer, &cell);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &cell);
            }
        }
}
