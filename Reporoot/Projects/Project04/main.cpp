#include <SDL2/SDL.h>
#include "Game.h"
#include <iostream>

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Bejeweled", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Game game;
    bool quit = false;
    SDL_Event event;

    // To track gem selection for swapping:
    int selectedRow = -1, selectedCol = -1;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                quit = true;

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int col = event.button.x / 50;
                int row = event.button.y / 50;

                if (selectedRow == -1 && selectedCol == -1) {
                    selectedRow = row;
                    selectedCol = col;
                    std::cout << "Selected first gem: (" << selectedRow << ", " << selectedCol << ")\n";
                }
                else {
                    std::cout << "Selected second gem: (" << row << ", " << col << ")\n";
                    if (game.isAdjacent(selectedRow, selectedCol, row, col)) {
                        game.swap(selectedRow, selectedCol, row, col);
                    }
                    else {
                        std::cout << "Gems not adjacent, swap ignored.\n";
                    }
                    selectedRow = -1;
                    selectedCol = -1;
                }
            }

            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_r) {
                    game = Game(); // Restart the game
                    selectedRow = selectedCol = -1;
                    std::cout << "Game restarted\n";
                }
            }
        }

        game.play();

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        game.draw(renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(100);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}