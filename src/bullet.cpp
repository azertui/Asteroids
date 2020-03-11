#include "../include/bullet.h"

void bullet::move(){
    if(!remove){
        if(--ttl>0){
            p1.x+=vx;
            p1.y+=vy;
            p1.x=adjust(p1.x,game->width);
            p1.y=adjust(p1.y,game->height);
        }else{
            remove=true;
        }
    }
}

void bullet::draw(SDL_Renderer *renderer) const{
    if(!remove){
        SDL_FPoint tmp={p2.x*cosf(angle) - p2.y * sinf(angle),
        p2.x*sinf(angle) + p2.y * cosf(angle)};
        tmp.x+=p1.x;
        tmp.y+=p1.y;
        SDL_RenderDrawLineF(renderer,p1.x,p1.y,tmp.x,tmp.y);
    }
}