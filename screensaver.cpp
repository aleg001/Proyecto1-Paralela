#include "screensaver.h"

// Global variables for window and renderer
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

// Function to initialize SDL (Simple DirectMedia Layer)
bool initializeSDL() {
    // Initialize SDL for video (graphics) subsystem
    return SDL_Init(SDL_INIT_VIDEO) == 0;
}

// Function to initialize SDL_ttf (TrueType Font support)
bool initializeTTF() {
    // Initialize SDL_ttf for text rendering
    return TTF_Init() == 0;
}

// Function to load a TrueType font from a file
TTF_Font* loadFont(const char* fontPath, int fontSize) {
    // Open the font file with the specified size
    return TTF_OpenFont(fontPath, fontSize);
}

// Function to create an SDL window with the given title, width, and height
SDL_Window* createWindow(const char* title, int width, int height) {
    // Create a window with specified parameters
    return SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
}

// Function to create an SDL renderer associated with a window
SDL_Renderer* createRenderer(SDL_Window* window) {
    // Create a hardware-accelerated renderer for the given window
    return SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

// Función para actualizar el movimiento de los círculos basado en la física
void updatePhysics(vector<BALL>& circles) {
    for (int i = 0; i < circles.size(); ++i) {
        // Actualizar la posición basada en la velocidad actual
        circles[i].x += circles[i].xVel;
        circles[i].y += circles[i].yVel;

        // Verificar colisiones con los bordes y cambiar la velocidad
        if (circles[i].x - CIRCLE_RADIUS < 0 || circles[i].x + CIRCLE_RADIUS > SCREEN_WIDTH) {
            circles[i].xVel = -circles[i].xVel; // Cambiar dirección en X
        }

        if (circles[i].y - CIRCLE_RADIUS < 0 || circles[i].y + CIRCLE_RADIUS > SCREEN_HEIGHT) {
            circles[i].yVel = -circles[i].yVel; // Cambiar dirección en Y
        }
    }

    // Verificar colisiones entre círculos y ajustar velocidades
    for (int i = 0; i < circles.size(); ++i) {
        for (int j = i + 1; j < circles.size(); ++j) {
            int dx = circles[j].x - circles[i].x;
            int dy = circles[j].y - circles[i].y;
            int distanceSquared = dx * dx + dy * dy;

            // Si hay colisión entre dos círculos, ajustar sus velocidades
            if (distanceSquared <= (2 * CIRCLE_RADIUS) * (2 * CIRCLE_RADIUS)) {
                // Implementar cálculos de colisión y ajuste de velocidad aquí
                // Puedes utilizar principios de física, como la conservación de momento
            }
        }
    }
}

// Función para obtener un color aleatorio
SDL_Color getRandomColor() {
    SDL_Color color;
    color.r = rand() % 256;
    color.g = rand() % 256;
    color.b = rand() % 256;
    return color;
}


// Function to initialize the positions and colors of circles
void initializeCircles(vector<BALL>& circles) {
    for (int i = 0; i < circles.size(); ++i) {
        // Initialize circle positions and colors randomly
        circles[i].x = rand() % (SCREEN_WIDTH - 2 * CIRCLE_RADIUS) + CIRCLE_RADIUS;
        circles[i].y = rand() % (SCREEN_HEIGHT - 2 * CIRCLE_RADIUS) + CIRCLE_RADIUS;
        circles[i].color = getRandomColor();
    }
}

// Function to handle SDL events (e.g., quitting the application)
void handleEvents(bool& quit) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
    }
}

// Function to render circles and FPS text on the screen
void render(SDL_Renderer* renderer, const vector<BALL>& circles, TTF_Font* font, int displayedFPS) {
    // Clear the renderer with a blue background
    SDL_SetRenderDrawColor(renderer, 0, 102, 255, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < circles.size(); ++i) {
        // Render filled circles with their respective colors
        SDL_SetRenderDrawColor(renderer, circles[i].color.r, circles[i].color.g, circles[i].color.b, 255);
        renderFilledCircle(renderer, circles[i].x, circles[i].y, CIRCLE_RADIUS);
    }

    // Display the current frames per second (FPS)
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

    // Present the renderer to display the updated content
    SDL_RenderPresent(renderer);
}

// Function to calculate and update frames per second (FPS)
void calculateFPS(Uint32 frameTime, int& displayedFPS) {
    if (frameTime > 0) {
        // Calculate FPS based on frame time
        displayedFPS = 1000 / frameTime;
    }
}

// Function to clean up resources and quit SDL
void cleanup(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font) {
    // Clean up the renderer, window, and font
    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
    }

    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }

    if (font != nullptr) {
        TTF_CloseFont(font);
    }

    // Quit SDL and SDL_ttf
    TTF_Quit();
    SDL_Quit();
}
