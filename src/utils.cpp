#include "../include/utils.h"

double adjust(double x,int threshold){
    return x>=threshold?x-threshold:x<=0?x+threshold:x;
}

void add(int n,SDL_Point tab[], SDL_Point p){
    for(int k=0;k<n;k++){
        tab[k].x+=p.x;
        tab[k].y+=p.y;
    }
}

void add(int n,SDL_FPoint tab[], SDL_FPoint p){
    for(int k=0;k<n;k++){
        tab[k].x+=p.x;
        tab[k].y+=p.y;
    }
}

void sub(int n,SDL_Point tab[], SDL_Point p){
    for(int k=0;k<n;k++){
        tab[k].x-=p.x;
        tab[k].y-=p.y;
    }
}