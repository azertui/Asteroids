#include "../include/modules.h"
#include <iostream>
Obstacle* getRandomObstacle(float x, float y, int s, Parameters* g){
    int rd= rand()%M_End;
    Obstacle * obs;
    //add your module's constructor call here
    switch (rd)
    {
    case M_tracker:
        obs = new Tracker(x,y,s,g);
        break;
    default:
        obs = new Asteroid(x,y,s,g);
    }
    return obs;
}

SpaceShip* getRandomSpaceShip(float x,float y,Parameters *g){
    int rd=rand()%M_SEnd;
    SpaceShip* sh;
    switch (rd)
    {
    case M_Turret:
        sh = new Turret(x,y,g);
        break;
    
    default:
        sh = new Turret(x,y,g);
        break;
    }
    return sh;
}