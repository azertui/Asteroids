#include <ship.h>

void Ship::generate(){
    points[0].y=-game->cst_ssize/2;
    points[0].x=-game->cst_ssize/2;
    points[1].y=points[0].y;
    points[1].x=game->cst_ssize/2;
    points[2].y=game->cst_ssize;
    points[2].x=0;
    vx=0;
    vy=0;
}

void Ship::draw(SDL_Renderer *renderer){
    SDL_FPoint tmp[3];
    drawLives(renderer);
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
    if(game->shoot){
        //std::cout << "pew pew" << std::endl;
        bullet b=bullet(pos,angle,game);
        bullets.emplace_front(b);
    }
}

/* Get the 3 points constituting the ship considering the angle and the position */
void Ship::getPoints(SDL_FPoint result[]) const{
    for(int i=0;i<3;i++){
        result[i].x=points[i].x*cosf(angle) - points[i].y*sinf(angle);
        result[i].y=points[i].x*sinf(angle) + points[i].y*cosf(angle);
    }
    add(3, result, pos);
    return;
}

std::_Fwd_list_iterator<bullet> Ship::getBulletsBegin() {
    return bullets.begin();
}

std::_Fwd_list_iterator<bullet> Ship::getBulletsEnd() {
    return bullets.end();
}

void Ship::drawLives(SDL_Renderer *renderer) {
    SDL_FPoint shift = 
        {static_cast <float> (game->cst_ssize),static_cast <float> (game->cst_ssize*2)};
    points[0].y*=-1;points[1].y*=-1;points[2].y*=-1;
    for (int i=0; i<lives; i++) {
        add(3,points,shift);
        SDL_RenderDrawLinesF(renderer,points,3);
        SDL_RenderDrawLineF(renderer,points[2].x,points[2].y,points[0].x,points[0].y);
        sub(3,points,shift);
        shift.x+=game->cst_ssize*1.2;
    }
    points[0].y*=-1;points[1].y*=-1;points[2].y*=-1;
}

void Ship::updateBullets(){
    bool first=true;
    std::_Fwd_list_iterator<bullet> prev=bullets.begin();
    auto i=bullets.begin();
    while (i!=bullets.end()){
        if(i->remove){
            i++;
            if(!first) {
                bullets.erase_after(prev);
            }
            else {
                bullets.pop_front();
                prev = bullets.begin();
            }
            //std::cout<<"peeeeeew~"<<std::endl;
        }else{
            i->move();
            if(!first)
                prev++;
            else
                first=false;
            i++;
        }
    }
}

void Ship::drawBullets(SDL_Renderer *rend){
    for(auto b=bullets.begin();b!=bullets.end();b++){
        if(!b->remove)
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
        // std::cout << vx << " " << vy << std::endl;
    } else if(game->back && !game->forward){
        speed=-game->thruster_acc;
        vx-=sin(angle)*speed;
        vy+=cos(angle)*speed;
        // std::cout << vx << " " << vy << std::endl;
    }
}

void Ship::move(){
    updateBullets();
    pos.x+=vx;
    pos.y+=vy;
    pos.x=adjust(pos.x,game->width);
    pos.y=adjust(pos.y,game->height);
}

int Ship::respawn(){
    lives--;
    if (lives>0) {
        pos.x = static_cast <float> (game->width)/2;
        pos.y = static_cast <float> (game->height)/2;
        vx = vy = speed = 0;
        angle = 0;
    }
    return lives;
        
}

const SDL_FPoint* Ship::getPosition() const{
    const SDL_FPoint* p=&pos;
    return p;
}