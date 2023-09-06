#include "screensaver.h"

int main(int argc, char* argv[]) {
    // Verifica si se proporciona el número de círculos como argumento
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <Number of circles>" << endl;
        return 1; // Retorna 1 para indicar un error
    }

    // Convierte el argumento en un número de círculos
    int numCircles = atoi(argv[1]);

    // Verifica que el número de círculos sea válido (mayor que 0)
    if (numCircles <= 0) {
        cout << "The number of circles must be greater than 0" << endl;
        return 1; // Retorna 1 para indicar un error
    }

    // Inicializa SDL (Simple DirectMedia Layer)
    if (!initializeSDL()) {
        cout << "Failed to initialize SDL." << endl;
        return 1; // Retorna 1 para indicar un error
    }

    // Inicializa SDL_ttf (TrueType Font support) para texto
    if (!initializeTTF()) {
        cout << "Failed to initialize SDL_ttf." << endl;
        return 1; // Retorna 1 para indicar un error
    }

    // Carga una fuente TTF
    TTF_Font* font = loadFont("Poppins.ttf", 14);
    if (font == nullptr) {
        cout << "Failed to load font." << endl;
        return 1; // Retorna 1 para indicar un error
    }

    // Crea una ventana SDL
    SDL_Window* window = createWindow("Screensaver", SCREEN_WIDTH, SCREEN_HEIGHT);
    if (window == nullptr) {
        cout << "Failed to create window." << endl;
        return 1; // Retorna 1 para indicar un error
    }

    // Crea un renderizador SDL asociado a la ventana
    SDL_Renderer* renderer = createRenderer(window);
    if (renderer == nullptr) {
        cout << "Failed to create renderer." << endl;
        return 1; // Retorna 1 para indicar un error
    }

    // Inicializa la generación de números aleatorios
    srand(time(0));

    // Crea un vector de círculos y los inicializa
    vector<Circle> circles(numCircles);
    initializeCircles(circles);

    Uint32 frameStart, frameTime;
    int displayedFPS = 0;
    bool quit = false;

    while (!quit) {
        frameStart = SDL_GetTicks(); // Obtiene el tiempo de inicio del cuadro
        handleEvents(quit); // Maneja eventos de SDL
        render(renderer, circles, font, displayedFPS); // Renderiza círculos y FPS
        frameTime = SDL_GetTicks() - frameStart; // Calcula el tiempo transcurrido en el cuadro
        calculateFPS(frameTime, displayedFPS); // Calcula y actualiza los FPS
    }

    // Limpia y libera recursos
    cleanup(renderer, window, font);

    return 0; // Retorna 0 para indicar una ejecución exitosa
}
