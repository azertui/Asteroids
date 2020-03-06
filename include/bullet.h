#ifndef BULLET_H
#define BULLET_H
#include <parameters.h>
#include <cmath>
#include <SDL2/SDL.h>
#include <utils.h>
class bullet
{
private:
    double vx,vy,angle;
    int ttl;
    Parameters *game;
public:
    bool remove;
    SDL_FPoint p1,p2;
    bullet(SDL_FPoint a,SDL_FPoint b,double ang,Parameters* p){
        remove=false;
        game=p;
        angle=ang;
        p1=a;
        p2=b;
        vx=sin(angle)*game->bullet_speed;
        vx=-cos(angle)*game->bullet_speed;
        ttl=game->bullet_life_s*game->cst_fps;
    }
    void move();
    void draw(SDL_Renderer *renderer);
};

#endif