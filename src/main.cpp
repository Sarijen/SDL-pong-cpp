#include <SDL.h>
#include "game.h"
#include "rendering.h"
#undef main

int main(int argc, char* argv[]) { 

    bool isRunning = true;
    SDL_Event event;

    Render renderer;
    Game game(renderer);

    while (isRunning) { 
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }
        game.HandleInput(event);
        game.Update();
        game.RenderGameObjects();
        SDL_Delay(10);
    }
    return 0;
}