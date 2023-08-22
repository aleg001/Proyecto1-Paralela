#ifndef SCREENSAVER_H
#define SCREENSAVER_H

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
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
};


#endif
