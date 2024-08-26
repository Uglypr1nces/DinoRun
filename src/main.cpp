#include <SDL2/SDL.h>
#include <iostream>

//screen dimensions
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;


//main function
int main(int argc, char* args[]){
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

// Create a window
    SDL_Window* window = SDL_CreateWindow("My First Game",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH,
                                          SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Main game loop
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        // Handle events on the queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        // Draw here (e.g., a rectangle)
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_Rect fillRect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        SDL_RenderFillRect(renderer, &fillRect);

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}