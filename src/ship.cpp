#include "../include/ship.h"

void Ship::generate(){
    points[0].y=-game->cst_ssize/2;
    points[0].x=-game->cst_ssize/2;
    points[1].y=points[0].y;
    points[1].x=game->cst_ssize/2;
    points[2].y=game->cst_ssize;
    points[2].x=0;
}

void Ship::draw(SDL_Renderer *renderer){
    SDL_Point tmp[3];
    for(int i=0;i<3;i++){
        tmp[i].x=((double)points[i].x)*cosf(angle) - ((double)points[i].y)*sinf(angle);
        tmp[i].y=((double)points[i].x)*sinf(angle) + ((double)points[i].y)*cosf(angle);
    }
    add(3,tmp,pos);
    //SDL_RenderDrawPoint(renderer,pos.x,pos.y);
    SDL_RenderDrawLines(renderer,tmp,3);
    SDL_RenderDrawLine(renderer,tmp[2].x,tmp[2].y,tmp[0].x,tmp[0].y);
}

void Ship::move(){
    if(game->right){
        angle+=0.00001;
    }
    if(game->left){
        angle-=0.00001;
    }
    if(game->forward && !game->back){
        speed=game->thruster_acc;
        vx=sin(angle)*speed;
        vy=cos(angle)*speed;
        std::cout << vx << " " << vy << std::endl;
    } else if(game->back && !game->forward){
        speed=-game->thruster_acc;
        vx=sin(angle)*speed;
        vy=cos(angle)*speed;
        std::cout << vx << " " << vy << std::endl;
    }
    pos.x+=vx;
    pos.y+=vy;
    pos.x=adjust(pos.x,game->width);
    pos.y=adjust(pos.y,game->height);
}