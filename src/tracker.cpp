#include "../include/tracker.h"
#include <iostream>

void Tracker::draw(SDL_Renderer *renderer){
    if(size>0){
        Uint8 r,g,b,a;
        if(SDL_GetRenderDrawColor(renderer,&r,&g,&b,&a)<0){
            std::cout << "tracker.draw: SDL_GetRenderDrawColor: "<< SDL_GetError()<<std::endl;
            r=g=a=255;
        }
        SDL_SetRenderDrawColor(renderer,254,0,246,255);
        
        SDL_FPoint tmp[npoints];
        for(int i=0;i<npoints;i++){
            tmp[i].x=points[i].x*cosf(angle) - points[i].y*sinf(angle);
            tmp[i].y=points[i].x*sinf(angle) + points[i].y*cosf(angle);
        }
        
        add(npoints,tmp,pos);
        SDL_RenderDrawLinesF(renderer,tmp,npoints);
        SDL_RenderDrawLineF(renderer,tmp[npoints-1].x,tmp[npoints-1].y,tmp[0].x,tmp[0].y);
        SDL_SetRenderDrawColor(renderer,r,g,b,a);
    }
}

void Tracker::generate(){
    float sz = static_cast <float> (size*15);
    radius =sz;
    float angle=0;
    points[0]={-sz/2,-sz/2};
    points[1]={sz/2,-sz/2};
    points[3]={-sz/2,sz/2};
    points[2]={sz/2,sz/2};
}

void Tracker::move(){
    SDL_FPoint player = game->getPlayerPosition();
    vx+=(-pos.x+player.x)/20;
    vy+=(-pos.y+player.y)/20;
    vx=bornes(vx,min_speed,max_speed);
    vy=bornes(vy,min_speed,max_speed);
    pos.x+=vx;
    pos.y+=vy;
    pos.x=adjust(pos.x,game->width);
    pos.y=adjust(pos.y,game->height);
    angle+=0.5*(vx+vy)/(2.0*max_speed);
}

bool Tracker::checkObjectCollision(SDL_FPoint objPoints[], SDL_FPoint objPos, int n){
    SDL_FPoint tmp[npoints];
        for(int i=0;i<npoints;i++){
            tmp[i].x=points[i].x*cosf(angle) - points[i].y*sinf(angle);
            tmp[i].y=points[i].x*sinf(angle) + points[i].y*cosf(angle);
        }
        add(npoints,tmp,pos);
        for (int i = 0; i < n; i++)
        {
            double dx = objPoints[i].x - pos.x,
                   dy = objPoints[i].y - pos.y;
            if ((dx >= -radius / 2 && dx <= radius / 2) || (dy >= -radius / 2 && dy <= radius / 2))
            {
                for (int k = 0; k < npoints; k++)
                {
                    if(segmentsIntersect(tmp[k],tmp[(k+1)%npoints],objPoints[i],objPoints[(i+1)%n]))
                        return true;
                }
            }
        }
        return false;
}

std::list<Obstacle*> Tracker::split(){
    std::list<Obstacle*> l;
    game->score+=200*size;
    if(size>1){
        Obstacle* obs;
        for(int i=0;i<size;i++){
            int rx=10+rand()%20,
            ry=10+rand()%20;
            rx=rand()%2?rx:-rx;
            ry=rand()%2?ry:-ry;
            obs = new Tracker(pos.x+rx,pos.y+ry,size-1,game);
            l.emplace_front(obs);
        }
    }
    return l;
}