#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

int PLAYER_WIDTH = 80;
int PLAYER_HEIGHT = 60;

bool isJumping = false;
int jumpVelocity = -35;
int gravity = 1;
int groundY = SCREEN_HEIGHT - PLAYER_HEIGHT;

class Object {      
public:      
    int width, height;
    int x, y;
    Uint8 red, green, blue, alpha;
    SDL_Renderer* renderer;

    Object(int w, int h, SDL_Renderer* rend, int xpos, int ypos, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255)
        : width(w), height(h), x(xpos), y(ypos), red(r), green(g), blue(b), alpha(a), renderer(rend) {}

    void drawObject() {
        SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
        SDL_Rect object = {x, y, width, height};
        SDL_RenderFillRect(renderer, &object);
    }

    void moveObject(int add_x, int add_y) {
        x -= add_x;
        y -= add_y;
        drawObject();
    }

    bool checkCollision(Object& other) {
        return x < other.x + other.width && x + width > other.x &&
               y < other.y + other.height && y + height > other.y;
    }
};

Object generateObstacle(SDL_Renderer* renderer) {
    int obstacleHeight = rand() % 100 + 50;
    return Object(50, obstacleHeight, renderer, SCREEN_WIDTH, groundY - obstacleHeight, 0, 255, 0);
}

int main(int argc, char* args[]) {
    srand(static_cast<unsigned>(time(0)));

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

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

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    bool quit = false;
    SDL_Event e;

    Object player(PLAYER_WIDTH, PLAYER_HEIGHT, renderer, 50, groundY - PLAYER_HEIGHT, 255, 0, 0);
    Object ground(SCREEN_WIDTH, PLAYER_HEIGHT / 2, renderer, 0, groundY, 255, 255, 255);

    std::vector<Object> obstacles;
    int obstacleTimer = 0;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE && !isJumping) {
                isJumping = true;
                jumpVelocity = -35;  // Reset jump velocity when the jump starts
            }
        }

        // Handle jumping
        if (isJumping) {
            player.y += jumpVelocity;
            jumpVelocity += gravity;

            if (player.y >= groundY - PLAYER_HEIGHT) {
                player.y = groundY - PLAYER_HEIGHT;
                isJumping = false;
            }
        }

        // Add obstacles at intervals
        obstacleTimer++;
        if (obstacleTimer > 100) {
            obstacles.push_back(generateObstacle(renderer));
            obstacleTimer = 0;
        }

        // Move and check obstacles
        for (auto it = obstacles.begin(); it != obstacles.end();) {
            it->moveObject(5, 0);

            // Remove off-screen obstacles
            if (it->x + it->width < 0) {
                it = obstacles.erase(it);
            } else {
                // Check collision with player
                if (player.checkCollision(*it)) {
                    std::cout << "Game Over! Dino hit an obstacle." << std::endl;
                    quit = true;
                }
                ++it;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        // Draw objects
        player.drawObject();
        ground.drawObject();

        for (auto& obstacle : obstacles) {
            obstacle.drawObject();
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
