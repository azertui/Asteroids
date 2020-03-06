#include <ship.h>

void Ship::generate(){
    points[0].y=-game->cst_ssize/2;
    points[0].x=-game->cst_ssize/2;
    points[1].y=points[0].y;
    points[1].x=game->cst_ssize/2;
    points[2].y=game->cst_ssize;
    points[2].x=0;
}

void Ship::draw(SDL_Renderer *renderer){
    SDL_FPoint tmp[3];
    drawBullets(renderer);
    for(int i=0;i<3;i++){
        tmp[i].x=points[i].x*cosf(angle) - points[i].y*sinf(angle);
        tmp[i].y=points[i].x*sinf(angle) + points[i].y*cosf(angle);
    }
    add(3,tmp,pos);
    SDL_RenderDrawPointF(renderer,pos.x,pos.y);
    SDL_RenderDrawLinesF(renderer,tmp,3);
    SDL_RenderDrawLineF(renderer,tmp[2].x,tmp[2].y,tmp[0].x,tmp[0].y);
}

void Ship::shoot(){
    SDL_FPoint tmp=points[2];
    tmp.x+=pos.x;
    tmp.y+=pos.y;
    bullet b=bullet(pos,tmp,angle,game);
    bullets.push_front(b);
}

void Ship::updateBullets(){
    for(auto b=bullets.begin();b!=bullets.end();b++){
        if(!b->remove)
            b->move();
        else
            bullets.pop_back();
    }
}

void Ship::drawBullets(SDL_Renderer *rend){
    for(auto b=bullets.begin();b!=bullets.end();b++){
        b->draw(rend);
    }
}

void Ship::applyEvents(){
    if(game->right){
        angle+=game->angleChange;
    }
    if(game->left){
        angle-=game->angleChange;
    }
    if(game->forward && !game->back){
        speed=game->thruster_acc;
        vx-=sin(angle)*speed;
        vy+=cos(angle)*speed;
        std::cout << vx << " " << vy << std::endl;
    } else if(game->back && !game->forward){
        speed=-game->thruster_acc;
        vx-=sin(angle)*speed;
        vy+=cos(angle)*speed;
        std::cout << vx << " " << vy << std::endl;
    }
}

void Ship::move(){
    updateBullets();
    pos.x+=vx;
    pos.y+=vy;
    pos.x=adjust(pos.x,game->width);
    pos.y=adjust(pos.y,game->height);
}