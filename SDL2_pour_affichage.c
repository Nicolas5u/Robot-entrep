#include "declaration.h"

/* ***************************************************

Programme qui contient les fonctions nécessaires pour l'affichage avec SDL2

*************************************************** */
// pour SDL2
const int SCREEN_WIDTH = 800;    // taille de la fenêtre en pixel (lignes)
const int SCREEN_HEIGHT = 600;   // taille de la fenêtre en pixel (colonnes)
const int CELL_SIZE = 60;         // taille de chaque case


int affichage(){
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {                                                        // pour l'initialisation
        printf("Erreur SDL : %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Les malheurs de l'entrepôt",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);

    if (!window) {                                                                             // pour l'initialisation
        printf("Erreur fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {                                                                           // pour l'initialisation
        printf("Erreur renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int quit = 0;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = 1;
        }

        // écran avec un fond noir
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // noir
        SDL_RenderClear(renderer);

        // Dessine la grille
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // blanc

        for (int row = 0; row < NB_LIGNE; row++) {
            for (int col = 0; col < NB_LIGNE; col++) {
                SDL_Rect cell = {
                    col * CELL_SIZE,
                    row * CELL_SIZE,
                    CELL_SIZE,
                    CELL_SIZE
                };
                SDL_RenderDrawRect(renderer, &cell);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
