#ifndef SHIP_H
#define SHIP_H
#include <SDL2/SDL.h>
#include "parameters.h"
#include "../include/utils.h"
#include <cmath>
#include <bullet.h>
#include <list>

class Ship{
    public:
    SDL_FPoint pos;
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
    void applyEvents();
    private:
    std::list<bullet> bullets;
    Parameters *game;
    SDL_FPoint points[3];
    double vx,vy,speed;
    void updateBullets();
    void drawBullets(SDL_Renderer*);
    void generate();
    void shoot();
};

#endif