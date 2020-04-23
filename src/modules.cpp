#include "../include/modules.h"

Obstacle* getRandomObstacle(float x, float y, int s, Parameters* g){
    int rd= rand()%M_End;
    Obstacle * obs;
    //add your module's constructor call here
    switch (rd)
    {
    case 1:
        obs = new Tracker(x,y,s,g);
        break;
    default:
        obs = new Asteroid(x,y,s,g);
    }
    return obs;
}