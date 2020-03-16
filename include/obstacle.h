#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <cmath>
#include <cstdlib>
#include "../include/parameters.h"
#include "../include/utils.h"

class Obstacle
{
public:
    SDL_FPoint pos;
    int size;
    Obstacle(){
        size=0;
        npoints=0;
    }
    ~Obstacle(){
    }
    Obstacle(float x, float y, int s,Parameters *g)
    {
        game=g;
        pos = {x, y};
        size = s;
        generate();
        init_movement();
    }
    void draw(SDL_Renderer *renderer);
    void move();
    bool checkObjectCollision(SDL_FPoint objPoints[], SDL_FPoint objPos, int n);
private:
    Parameters *game;
    int npoints;
    SDL_FPoint points[20];
    double ax,ay,vx,vy;
    void generate();
    void init_movement();
};



#endif