#ifndef TRACKER_H
#define TRACKER_H

#include "obstacle.h"

class Tracker : public Obstacle
{
    public:
    Tracker(){
        size=0;
        npoints=0;
    }

    Tracker(float x,float y, int s, Parameters* g){
        game=g;
        pos={x,y};
        npoints = 4;
        size=s;
        generate();
    }
    void draw(SDL_Renderer *renderer);
    void generate();
    void move();
    void init_movement(){};
    bool checkObjectCollision(SDL_FPoint objPoints[], SDL_FPoint objPos, int n);
    std::list<Obstacle*> split();
    int getScore();
    private:
        double radius,max_speed = 5,
        min_speed = 0.5;
};

#endif