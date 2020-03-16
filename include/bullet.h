#ifndef BULLET_H
#define BULLET_H
#include <parameters.h>
#include <cmath>
#include <SDL2/SDL.h>
#include <utils.h>
#include <vector>

class bullet
{
private:
    double vx,vy,angle;
    int ttl;
    Parameters *game;
public:
    bool remove;
    SDL_FPoint p1,p2;
    bullet(SDL_FPoint a,double ang,Parameters* p){
        remove=false;
        game=p;
        angle=ang;
        p1=a;
        p2.x=0;
        p2.y=game->cst_ssize/3;
        vx=-sin(angle)*game->bullet_speed;
        vy=cos(angle)*game->bullet_speed;
        ttl=game->bullet_life_s*game->cst_fps;
    }
    void move();
    void draw(SDL_Renderer *renderer) const;
    std::vector<SDL_FPoint> getBoundingBox() const;
};

#endif