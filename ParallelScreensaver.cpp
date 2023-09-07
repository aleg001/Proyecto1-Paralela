#include "screensaver.h"
#include "omp.h"

// Global variables for the window and renderer
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

// Function to generate a random color
SDL_Color GenerateRandomColor() {
    SDL_Color color;
    color.r = rand() % 256;
    color.g = rand() % 256;
    color.b = rand() % 256;
    return color;
}

// Function to render a filled circle in the SDL renderer
void RenderFilledCircle(SDL_Renderer* renderer, int x, int y, int radius) {
    SDL_Rect rect;
    rect.x = x - radius;
    rect.y = y - radius;
    rect.w = radius * 2;
    rect.h = radius * 2;

    for (int dy = -radius; dy <= radius; dy++) {
        int lineWidth = static_cast<int>(sqrt(radius * radius - dy * dy) * 2 + 0.5);
        int lineY = y + dy;
        SDL_Rect lineRect;
        lineRect.x = x - lineWidth / 2;
        lineRect.y = lineY;
        lineRect.w = lineWidth;
        lineRect.h = 1;
        SDL_RenderFillRect(renderer, &lineRect);
    }
}

// Function to initialize SDL
bool InitializeSDL() {
    return SDL_Init(SDL_INIT_VIDEO) == 0;
}

// Function to initialize SDL_ttf
bool InitializeTTF() {
    return TTF_Init() == 0;
}

// Function to load a TTF font
TTF_Font* LoadFont(const char* fontPath, int fontSize) {
    return TTF_OpenFont(fontPath, fontSize);
}

// Function to create an SDL window
SDL_Window* CreateWindow(const char* title, int width, int height) {
    return SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
}

// Function to create an SDL renderer
SDL_Renderer* CreateRenderer(SDL_Window* window) {
    return SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

// Function to initialize the positions and initial colors of the circles
void InitializeCircles(vector<BALL>& circles) {
    for (int i = 0; i < circles.size(); ++i) {
        circles[i].x = rand() % (SCREEN_WIDTH - 2 * CIRCLE_RADIUS) + CIRCLE_RADIUS;
        circles[i].y = rand() % (SCREEN_HEIGHT - 2 * CIRCLE_RADIUS) + CIRCLE_RADIUS;
        circles[i].color = GenerateRandomColor();
    }
}

// Function to handle SDL events
void HandleEvents(bool& quit) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
    }
}

// Function to render the scene
void Render(SDL_Renderer* renderer, const vector<BALL>& circles, TTF_Font* font, int displayedFPS) {
    // Clear the renderer with a background color
    SDL_SetRenderDrawColor(renderer, 0, 102, 255, 255);
    SDL_RenderClear(renderer);

    // Render the circles
    for (int i = 0; i < circles.size(); ++i) {
        SDL_SetRenderDrawColor(renderer, circles[i].color.r, circles[i].color.g, circles[i].color.b, 255);
        RenderFilledCircle(renderer, circles[i].x, circles[i].y, CIRCLE_RADIUS);
    }

    // Render the FPS text
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

    // Present the renderer
    SDL_RenderPresent(renderer);
}

// Function to calculate the FPS
void CalculateFPS(Uint32 frameTime, int& displayedFPS) {
    if (frameTime > 0) {
        displayedFPS = 1000 / frameTime;
    }
}

// Function to clean up SDL and SDL_ttf resources
void Cleanup(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font) {
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

// Function to move circles randomly
void MoveCircles(vector<BALL>& circles) {
    for (int i = 0; i < circles.size(); ++i) {
        // Update the positions of circles here (e.g., add some velocity to x and y)
        circles[i].x += ((rand() % 3) - 1) * (SCREEN_WIDTH / 50); // Random horizontal movement (-1, 0, 1)
        circles[i].y += ((rand() % 3) - 1) * (SCREEN_HEIGHT / 50); // Random vertical movement (-1, 0, 1)

        // Ensure circles stay within the screen boundaries
        circles[i].x = std::max(CIRCLE_RADIUS, std::min(circles[i].x, SCREEN_WIDTH - CIRCLE_RADIUS));
        circles[i].y = std::max(CIRCLE_RADIUS, std::min(circles[i].y, SCREEN_HEIGHT - CIRCLE_RADIUS));
    }
}


int main(int argc, char* argv[]) {
    int max_threads = omp_get_max_threads();
    omp_set_num_threads(max_threads);
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <Number of circles>" << endl;
        return 1;
    }

    int numCircles = atoi(argv[1]);

    if (numCircles <= 0) {
        cout << "The number of circles must be greater than 0" << endl;
        return 1;
    }

    if (!initializeSDL()) {
        cout << "Failed to initialize SDL." << endl;
        return 1;
    }

    if (!initializeTTF()) {
        cout << "Failed to initialize SDL_ttf." << endl;
        return 1;
    }

    cout << "SDL and SDL_ttf initialized successfully." << endl;


    // referencia literal a la ruta del archivo
    TTF_Font* font = loadFont("/usr/share/fonts/truetype/fonts-kalapi/Kalapi.ttf", 14);
    if (font == nullptr) {
        cout << "Failed to load font." << endl;
        return 1;
    }

    SDL_Window* window = createWindow("Screensaver", SCREEN_WIDTH, SCREEN_HEIGHT);
    if (window == nullptr) {
        cout << "Failed to create window." << endl;
        return 1;
    }

    SDL_Renderer* renderer = createRenderer(window);
    if (renderer == nullptr) {
        cout << "Failed to create renderer." << endl;
        return 1;
    }

    srand(time(0));

    vector<Circle> circles(numCircles);
    initializeCircles(circles);

    Uint32 frameStart, frameTime;
    int displayedFPS = 0;
    bool quit = false;
    int frameCount = 0;

    while (!quit) {
        frameStart = SDL_GetTicks();
        handleEvents(quit);
        //moveCircles(circles);
        if (frameCount == 5) {
            moveCircles(circles);
            frameCount = 0;
        }
        render(renderer, circles, font, displayedFPS);
        frameTime = SDL_GetTicks() - frameStart;
        calculateFPS(frameTime, displayedFPS);
        frameCount++;
    }

    cleanup(renderer, window, font);
    return 0;
}
