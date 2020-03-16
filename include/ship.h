#ifndef SHIP_H
#define SHIP_H
#include <SDL2/SDL.h>
#include "parameters.h"
#include "../include/utils.h"
#include <cmath>
#include <bullet.h>
#include <forward_list>

class Ship{
    public:
    bool hurt=false;
    SDL_FPoint pos;
    double angle=0;
    Ship(int x,int y,Parameters *g){
        pos.x=x;
        pos.y=y;
        game=g;
        lives=g->initial_nb_lives;
        generate();
        bullets=std::forward_list<bullet>();
    }
    void draw(SDL_Renderer *renderer);
    void move();
    void applyEvents();
    void shoot();
    void getPoints(SDL_FPoint result[]);
    int respawn();
    private:
    std::forward_list<bullet> bullets;
    Parameters *game;
    SDL_FPoint points[3];
    double vx,vy,speed;
    int lives;
    void drawLives(SDL_Renderer *renderer);
    void updateBullets();
    void drawBullets(SDL_Renderer*);
    void generate();
};

#endif