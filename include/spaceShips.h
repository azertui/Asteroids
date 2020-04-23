#ifndef SHIPS_H
#define SHIPS_H

#include <SDL2/SDL.h>
#include "parameters.h"
#include "utils.h"
#include "bullet.h"
#include <forward_list>

class SpaceShip{
    public:
        bool active =true;
        bool hurt = false;
        SDL_FPoint pos;
        double angle=0;
        virtual void draw(SDL_Renderer* renderer)=0;
        virtual void move()=0;
        virtual std::_Fwd_list_iterator<bullet> getBulletsBegin()=0;
        virtual std::_Fwd_list_iterator<bullet> getBulletsEnd()=0;
        virtual bool checkObjectCollision(SDL_FPoint objPoints[], SDL_FPoint objPos, int n)=0;
        bool isInactive(){return (!active && bullets.empty());}
        void setInactive(){active=false;}
    protected:
        std::forward_list<bullet> bullets;
        Parameters *game;
        SDL_FPoint points[20];
        int npoints;
        double vx,vy;
        int lives;
        virtual void updateBullets()=0;
        virtual void drawBullets(SDL_Renderer*)=0;
        virtual void generate()=0;
};

#endif