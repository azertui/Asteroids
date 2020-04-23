#ifndef MODULES_H
#define MODULES_H

//add your module's headers here
#include "asteroid.h"
#include "tracker.h"
#include "../include/turret.h"

#include "spaceShips.h"
#include "turret.h"

//add your module name here
typedef enum obstacles
{
    M_asteroid,
    M_tracker,
    M_End
} obstacles;

typedef enum ships
{
    M_Turret,
    M_SEnd
} ships;

//Spawn position x and y, size s, game parameters
//Add module's constructor calls in modules.cpp
Obstacle* getRandomObstacle(float x, float y, int s, Parameters* g);
SpaceShip* getRandomSpaceShip(float x,float y,Parameters *g);
#endif