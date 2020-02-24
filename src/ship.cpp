#include "../include/ship.h"

void Ship::generate(){
    points[0].y=pos.y-game->cst_ssize/2;
    points[0].x=pos.x-game->cst_ssize/2;
    points[1].y=points[0].y;
    points[1].x=pos.x+game->cst_ssize/2;
    points[2].y=pos.y-2*game->cst_ssize;
    points[2].x=pos.x;
}

void Ship::draw(SDL_Renderer *renderer){
    SDL_RenderDrawLines(renderer,points,3);
    SDL_RenderDrawLine(renderer,points[2].x,points[2].y,points[0].x,points[0].y);
}