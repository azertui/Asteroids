#ifndef PARAM_H
#define PARAM_H
#include <SDL2/SDL.h>
class Parameters{
    public:
    //Ralentissement appliqué à l'accélération
    #define VOID_RESISTANCE 0.02
    //If 1 then obstacles can slow down
    const bool obstacle_slowing= 0;
    const bool player_slowdown= 1;
    const int start_obstacles= 5;
    const int start_ships = 3;
    const int max_size_obstacles= 3;
    const double initial_acc_max= 2;
    const double initial_acc_min= 1;
    const double max_speed= 10;
    //Window parameters
    SDL_Window *window;
    SDL_Renderer *renderer;
    int width= 1280;
    int height= 720;
    const int cst_fps = 30;
    const int events_per_tick = 10;
    long int score =0;
    //Ship parameters
    const int initial_nb_lives=5;
    const int invincibility_s=2;
    int invincibility_ticks;
    const int eventApply=10;
    const int cst_ssize=32;
    const double thruster_acc = 0.7;
    const double bullet_speed = 14;
    const int bullet_life_s=1;
    const double bullet_cooldown=0.2;
    int bullet_ticks_cooldown;
    const double angleChange=0.2;
    bool forward,left,right,back,shoot;
    Parameters();
    SDL_FPoint getPlayerPosition() const;
    void setPlayerPosition(const SDL_FPoint*);
    private:
        const SDL_FPoint* player;
};

#endif