#ifndef SHIP_H
#define SHIP_H
#include <SDL2/SDL.h>
#include "parameters.h"

class Ship{
    public:
    SDL_Point pos;
    int angle;
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
    double vx,vy,ax,ay;

    void generate();
};

#endif