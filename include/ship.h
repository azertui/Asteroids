#ifndef SHIP_H
#define SHIP_H
#include "spaceShips.h"

class Ship : public SpaceShip{
    public:
    Ship(){

    };
    Ship(float x,float y,Parameters *g){
        npoints = 3;
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
    void getPoints(SDL_FPoint result[]) const;
    std::_Fwd_list_iterator<bullet> getBulletsBegin();
    std::_Fwd_list_iterator<bullet> getBulletsEnd();
    int respawn();
    const SDL_FPoint* getPosition() const;
    bool checkObjectCollision(SDL_FPoint objPoints[], SDL_FPoint objPos, int n);
    private:
    std::forward_list<bullet> bullets;
    Parameters *game;
    double vx,vy,speed;
    int lives;
    void drawLives(SDL_Renderer *renderer);
    void updateBullets();
    void drawBullets(SDL_Renderer*);
    void generate();
};

#endif