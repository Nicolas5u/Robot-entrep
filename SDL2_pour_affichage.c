#include "declaration.h"

/** Largeur de la fenêtre SDL */
const int SCREEN_WIDTH = 800;
/** Hauteur de la fenêtre SDL */
const int SCREEN_HEIGHT = 600;
/** Taille (en pixels) d'une cellule de l'entrepôt */
const int CELL_SIZE = 60;

/**
 * @brief Lance l'affichage graphique SDL avec contrôle du robot au clavier (z,q,s,d).
 * 
 * Initialise SDL, crée la fenêtre et le renderer, puis boucle sur les événements clavier
 * pour déplacer le robot. Affiche en continu l'entrepôt.
 * 
 * @param partie Pointeur vers la structure Partie contenant l'état de l'entrepôt.
 * @return int 0 si succès, 1 en cas d'erreur SDL.
 */
int affichage(Partie* partie, int tailleL, int tailleC) {
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

    int quit = 0;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDL_QUIT:
                    case SDLK_ESCAPE:
                        quit = 1;
                        break;
                    case SDLK_z:
                        deplacement_H(partie);
                        break;
                    case SDLK_s:
                        deplacement_B(partie,tailleC);
                        break;
                    case SDLK_q:
                        deplacement_G(partie);
                        break;
                    case SDLK_d:
                        deplacement_D(partie,tailleL);
                        break;
                }
            }
        }

        SDL2_Affiche_entrepot(renderer, partie, tailleL, tailleC);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

/**
 * @brief Exécute les commandes de déplacement depuis un fichier texte et affiche graphiquement.
 * 
 * Ouvre le fichier de commandes, lit caractère par caractère, exécute les déplacements,
 * affiche l'entrepôt après chaque commande avec un délai.
 * 
 * @param Commande_Du_Robot Nom du fichier texte contenant les commandes (z,q,s,d).
 * @param partie Pointeur vers la structure Partie contenant l'état de l'entrepôt.
 * @return int 0 si succès, 1 en cas d'erreur SDL ou fichier.
 */
int SDL2_fichier_commandes(const char* Commande_Du_Robot, Partie* partie, int tailleL, int tailleC) {
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
            case 'v': deplacement_B(partie,tailleC); break;
            case 'q':
            case '<': deplacement_G(partie); break;
            case 'd':
            case '>': deplacement_D(partie,tailleL); break;
            case ' ':
            case '\n':
            case '\r': break; // Ignorer espaces et sauts de ligne
            default:
                printf("Commande inconnue : %c\n", commande);
                break;
        }

        SDL2_Affiche_entrepot(renderer, partie, tailleL,tailleC);
        SDL_RenderPresent(renderer);
        SDL_Delay(300);
    }

    fclose(fichier);
    SDL_Delay(1000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

/**
 * @brief Affiche graphiquement l'entrepôt dans la fenêtre SDL.
 * 
 * Dessine chaque case avec une couleur en fonction de son type (mur, robot, boite, chemin).
 * 
 * @param renderer Le renderer SDL utilisé pour dessiner.
 * @param partie Pointeur vers la structure Partie contenant l'état de l'entrepôt.
 */
void SDL2_Affiche_entrepot(SDL_Renderer* renderer, Partie* partie,int tailleL,int tailleC) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int row = 0; row < tailleL; row++) {
        for (int col = 0; col < tailleC; col++) {
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

