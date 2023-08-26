#include "screensaver.h"

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

bool initializeSDL() {
    return SDL_Init(SDL_INIT_VIDEO) == 0;
}

bool initializeTTF() {
    return TTF_Init() == 0;
}