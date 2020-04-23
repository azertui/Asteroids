#ifndef GAME_H
#define GAME_H
#include "modules.h"
#include <ctime>
#include "spaceShips.h"
#include "ship.h"

class Game{
    private:
    Parameters parameters;
    std::_Fwd_list_iterator<bullet> bullets_begin, bullets_end;
    Ship player;
    std::list<Obstacle*> obstacles;
    std::list<SpaceShip*> ships;
    bool quit;
    int prevTicks,ticks,ticks_collision_ship;
    void draw();

    public:
    Game();
    int init();
    Parameters* getParameters();
    void loop();
};
#endif