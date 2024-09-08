#include <SDL2/SDL.h>
#include <iostream>

// Screen dimensions
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

// Player dimensions
int PLAYER_WIDTH = 80;
int PLAYER_HEIGHT = 60;

// Object class definition
class Object {      
public:      
    int width, height;
    int x, y;
    Uint8 red, green, blue, alpha;
    SDL_Renderer* renderer;

    // Constructor to initialize object color and position
    Object(int w, int h, SDL_Renderer* rend, int xpos, int ypos, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255)
        : width(w), height(h), x(xpos), y(ypos), red(r), green(g), blue(b), alpha(a), renderer(rend) {}

    // Method to draw the object
    void drawObject() {
        SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);  // Set the color
        SDL_Rect object = {x, y, width, height};                    // Create the rectangle
        SDL_RenderFillRect(renderer, &object);                      // Render the rectangle
    }

    // Method to move the object
    void moveObject(int add_x, int add_y) {
        x += add_x;
        y += add_y;
        drawObject();
    }
};

// Main function
int main(int argc, char* args[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("DinoRun",
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

    // Create the player object
    Object player(PLAYER_WIDTH, PLAYER_HEIGHT, renderer, 0, 0, 255, 0, 0); // A red player

    while (!quit) {
        // Handle events on the queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            // Key press handling
            switch (e.type) {
                case SDL_KEYDOWN:
                    printf("Key press detected\n");
                    player.moveObject(10,20);
                    break;

                case SDL_KEYUP:
                    printf("Key release detected\n");
                    break;

                default:
                    break;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        // Draw the player object
        player.drawObject();

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
