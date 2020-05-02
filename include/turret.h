#ifndef TURRET_H
#define TURRET_H

#include "spaceShips.h"
#include "bullet.h"
#include <forward_list>

class Turret : public SpaceShip
{
    public:
    Turret(){
        npoints=0;
    }
    Turret(float x, float y, Parameters *g){
        score = 100;
        game=g;
        pos={x,y};
        generate();
        init_movement();
        bullets = std::forward_list<bullet>();
    }
    void draw(SDL_Renderer *renderer);
    void move();
    bool checkObjectCollision(SDL_FPoint objPoints[], SDL_FPoint objPos, int n);
    std::_Fwd_list_iterator<bullet> getBulletsBegin();
    std::_Fwd_list_iterator<bullet> getBulletsEnd();
    private:
    void generate();
    void init_movement();
    void updateBullets();
    void drawBullets(SDL_Renderer* renderer);
    int max_inertia = 5;
    double radius;
    int ticksBeforeShot = 0;
    int minTicks=15;
    int maxTicks=30;
    std::forward_list<bullet> bullets;
};

#endif