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

void cleanup(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font) {
    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
    }

    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }

    if (font != nullptr) {
        TTF_CloseFont(font);
    }

    TTF_Quit();
    SDL_Quit();
}

void calculateFPS(Uint32 frameTime, int& displayedFPS) {
    if (frameTime > 0) {
        displayedFPS = 1000 / frameTime;
    }
}

void handleEvents(bool& quit) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
    }
}

void initializeCircles(vector<BALL>& circles) {
    for (int i = 0; i < circles.size(); ++i) {
        circles[i].x = rand() % (SCREEN_WIDTH - 2 * CIRCLE_RADIUS) + CIRCLE_RADIUS;
        circles[i].y = rand() % (SCREEN_HEIGHT - 2 * CIRCLE_RADIUS) + CIRCLE_RADIUS;
        circles[i].color = getRandomColor();
    }
}

void render(SDL_Renderer* renderer, const vector<BALL>& circles, TTF_Font* font, int displayedFPS) {
    SDL_SetRenderDrawColor(renderer, 0, 102, 255, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < circles.size(); ++i) {
        SDL_SetRenderDrawColor(renderer, circles[i].color.r, circles[i].color.g, circles[i].color.b, 255);
        renderFilledCircle(renderer, circles[i].x, circles[i].y, CIRCLE_RADIUS);
    }

    string fpsText = "FPS: " + to_string(displayedFPS);
    SDL_Color textColor = {255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, fpsText.c_str(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Rect textRect;
    textRect.x = 10;
    textRect.y = 10;
    textRect.w = textSurface->w;
    textRect.h = textSurface->h;

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);

    SDL_RenderPresent(renderer);
}
