
#include <SDL2/SDL.h>
#include <iostream>
#include <iomanip>

#include "defs.h"
#include "game/game.h"

Game* game = nullptr;

int main() {

    game = new Game();

    // Initialize SDL, Window, Renderer, Game elements, Display handler etc.
    game->init("Betel Leaf Eater Sahil", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, false);
        
    Uint32 frameStart;
    
    while(game->running()) {
        
        frameStart = SDL_GetTicks();
        
        game->handleEvents();
        game->update();
        game->render();
        
        Uint32 frameTime = SDL_GetTicks() - frameStart;
        
        if(frameTime < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - 1.0*frameTime);
        }

        // Count frames, and save FPS stats.
        Game::display->count_frame();
    }
    
    // Clean the game objects and heap.
    game->clean();
    
    return 0;

}

