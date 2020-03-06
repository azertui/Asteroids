#include "../include/bullet.h"

void bullet::move(){
    if(--ttl>0){
        std::cout<<ttl<<std::endl;
        p1.x+=vx;
        p1.y+=vy;
        p2.x+=vx;
        p2.y+=vy;
        p1.x=adjust(p1.x,game->width);
        p2.x=adjust(p2.x,game->width);

        p1.y=adjust(p1.y,game->height);
        p2.y=adjust(p2.y,game->height);
    }else{
        remove=true;
    }
}

void bullet::draw(SDL_Renderer *renderer){
    if(!remove){
        SDL_RenderDrawLineF(renderer,p1.x,p1.y,p2.x,p2.y);
    }
}