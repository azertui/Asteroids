#include "bullet.h"

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

std::vector<SDL_FPoint> bullet::getBoundingBox() const{
    std::vector<SDL_FPoint> v(2);
   SDL_FPoint tmp={p2.x*cosf(angle) - p2.y * sinf(angle),
        p2.x*sinf(angle) + p2.y * cosf(angle)};
    tmp.x+=p1.x;
    tmp.y+=p1.y;
    v[0]=p1;
    v[1]=tmp;
    return v;
}

void bullet::getBoundingBox(SDL_FPoint result[]) const{
   SDL_FPoint tmp={p2.x*cosf(angle) - p2.y * sinf(angle),
        p2.x*sinf(angle) + p2.y * cosf(angle)};
    tmp.x+=p1.x;
    tmp.y+=p1.y;
    result[0]=p1;
    result[1]=tmp;
    return;
}