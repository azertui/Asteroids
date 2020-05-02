#ifndef GAME_H
#define GAME_H
#include "modules.h"
#include "textDisplayer.h"
#include <ctime>
#include "spaceShips.h"
#include "ship.h"
#include <string>

class Game{
    private:
    Parameters parameters;
    std::_Fwd_list_iterator<bullet> bullets_begin, bullets_end;
    Ship player;
    std::list<Obstacle*> obstacles;
    std::list<SpaceShip*> ships;
    int score;
    bool quit;
    int ticks,ticks_collision_ship;
    Uint32 prevTicks;
    void draw();

    public:
    Game();
    int init();
    Parameters* getParameters();
    void loop();
};
#endif