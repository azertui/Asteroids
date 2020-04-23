#include "../include/parameters.h"

Parameters::Parameters(){
    forward=left=right=back=shoot=false;
    bullet_ticks_cooldown=bullet_cooldown*cst_fps;
    invincibility_ticks=invincibility_s*cst_fps;
}

SDL_FPoint Parameters::getPlayerPosition() const{
    SDL_FPoint pos = *player;
    return pos;
}

void Parameters::setPlayerPosition(const SDL_FPoint* p){
    player = p;
}