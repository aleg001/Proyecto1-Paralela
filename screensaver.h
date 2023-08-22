#ifndef SCREENSAVER_H
#define SCREENSAVER_H

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cmath>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int CIRCLE_RADIUS = 20;
const int MAX_CIRCLE_SPEED = 5;
const int FRAMES_PER_SECOND = 60;

struct BALL {
    int x, y;
    int xVel, yVel;
    SDL_Color color;
};

bool initializeSDL();
bool initializeTTF();
TTF_Font* loadFont(const char* fontPath, int fontSize);
SDL_Window* createWindow(const char* title, int width, int height);
SDL_Renderer* createRenderer(SDL_Window* window);
void initializeCircles(vector<BALL>& circles);
void handleEvents(bool& quit);
void render(SDL_Renderer* renderer, const vector<BALL>& circles, TTF_Font* font, int displayedFPS);
void calculateFPS(Uint32 frameTime, int& displayedFPS);
void cleanup(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font);

#endif
