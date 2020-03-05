#ifndef SHIP_H
#define SHIP_H
#include <SDL2/SDL.h>
#include "parameters.h"
#include "../include/utils.h"
#include <cmath>

class Ship{
    public:
    SDL_Point pos;
    double angle;
    Ship(int x,int y,Parameters *g){
        pos.x=x;
        pos.y=y;
        game=g;
        angle=0;
        generate();
    }
    void draw(SDL_Renderer *renderer);
    void move();
    private:
    Parameters *game;
    SDL_Point points[3];
    double vx,vy,speed;

    void generate();
};

#endif