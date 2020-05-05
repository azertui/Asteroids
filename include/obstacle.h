#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SDL.h>
#include <SDL_rect.h>
#include <cmath>
#include <cstdlib>
#include <list>
#include "parameters.h"
#include "utils.h"

class Obstacle
{
public:
    SDL_FPoint pos;
    int size;
    virtual void draw(SDL_Renderer *renderer)=0;
    virtual void move()=0;
    virtual bool checkObjectCollision(SDL_FPoint objPoints[], SDL_FPoint objPos, int n)=0;
    virtual std::list<Obstacle*> split()=0;
    virtual int getScore()=0;
protected:
    Parameters *game;
    int npoints;
    SDL_FPoint points[20];
    double ax,ay,vx,vy,angle;
    virtual void generate()=0;
    virtual void init_movement()=0;
};



#endif