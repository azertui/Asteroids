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

void sub(int n,SDL_FPoint tab[], SDL_FPoint p){
    for(int k=0;k<n;k++){
        tab[k].x-=p.x;
        tab[k].y-=p.y;
    }
}

bool segmentsIntersect(SDL_FPoint A, SDL_FPoint B, 
                       SDL_FPoint C, SDL_FPoint D) {
    return ((det(A,B,C)*det(A,B,D)<0) && ((det(C,D,A)*det(C,D,B)<0)));

}

float det(SDL_FPoint A, SDL_FPoint B, SDL_FPoint C) {
    return A.x*B.y+B.x*C.y+C.x*A.y-C.x*B.y-A.x*C.y-B.x*A.y;
}