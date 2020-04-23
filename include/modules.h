#ifndef MODULES_H
#define MODULES_H

//add your module's headers here
#include "asteroid.h"
#include "tracker.h"

//add your module name here
typedef enum obstacles
{
    M_asteroid,
    M_tracker,
    M_End
} obstacles;

//Spawn position x and y, size s, game parameters
//Add module's constructor calls in modules.cpp
Obstacle* getRandomObstacle(float x, float y, int s, Parameters* g);

#endif