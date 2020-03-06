#ifndef PARAM_H
#define PARAM_H
#include <iostream>
class Parameters{
    public:
    //Ralentissement appliqué à l'accélération
    #define VOID_RESISTANCE 0.02
    //If 1 then obstacles can slow down
    const bool obstacle_slowing= 0;
    const bool player_slowdown= 1;
    const int start_obstacles= 5;
    const int max_size_obstacles= 3;
    const double initial_acc_max= 0.1;
    const double initial_acc_min= 0.01;
    const double max_speed= 5;
    //Window parameters
    int width= 1000;
    int height= 600;
    const int cst_fps = 30;
    //Ship parameters
    const int eventApply=10;
    const int cst_ssize=32;
    const double thruster_acc = 0.0000001;
    const double bullet_speed = 0.2;
    const int bullet_life_s=1;
    const double bullet_cooldown=0.2;
    const double angleChange=0.0002;
    bool forward,left,right,back,shoot;
    Parameters(){
        forward=left=right=back=shoot=false;
    }
};
#endif