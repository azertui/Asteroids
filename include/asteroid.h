#ifndef ASTEROID_H
#define ASTEROID_H


#include "obstacle.h"

class Asteroid : public Obstacle
{
public:
    Asteroid(){
        size=0;
        npoints=0;
    }

    Asteroid(float x, float y, int s,Parameters *g)
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
    std::list<Obstacle*> split();
private:
    void generate();
    void init_movement();
};



#endif