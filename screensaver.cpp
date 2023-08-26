#include "screensaver.h"

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

bool initializeSDL() {
    return SDL_Init(SDL_INIT_VIDEO) == 0;
}

bool initializeTTF() {
    return TTF_Init() == 0;
}

TTF_Font* loadFont(const char* fontPath, int fontSize) {
    return TTF_OpenFont(fontPath, fontSize);
}

SDL_Window* createWindow(const char* title, int width, int height) {
    return SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
}

SDL_Renderer* createRenderer(SDL_Window* window) {
    return SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}