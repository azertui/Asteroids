#ifndef GAME_H
#define GAME_H
#include "modules.h"
#include <ctime>
#include "ship.h"

class Game{
    private:
    Parameters parameters;
    std::_Fwd_list_iterator<bullet> bullets_begin, bullets_end;
    Ship player;
    std::list<Obstacle*> obstacles;
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