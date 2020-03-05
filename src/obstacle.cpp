#include <SDL2/SDL.h>
#include <cmath>
#include <cstdlib>
#include "../include/parameters.h"
#include "../include/utils.h"

//Par defaut, octogone. Peut etre change en override generate npoints et points
class Obstacle
{
public:
    SDL_Point pos;
    int size;
    Obstacle(){
        size=0;
        npoints=0;
    }
    ~Obstacle(){
    }
    Obstacle(int x, int y, int s,Parameters *g)
    {
        game=g;
        pos = {x, y};
        size = s;
        generate();
        init_movement();
    }
    void draw(SDL_Renderer *renderer){
        if(size>0){
            add(npoints,points,pos);
            SDL_RenderDrawLines(renderer,points,npoints);
            SDL_RenderDrawLine(renderer,points[npoints-1].x,points[npoints-1].y,points[0].x,points[0].y);
            sub(npoints,points,pos);
        }
    }
    SDL_Point collisionPoint(SDL_Rect *r){
        SDL_Rect rect;
        SDL_EnclosePoints(points,npoints,r,&rect);
        return {rect.x+rect.w/2+rect.h/2,rect.y+rect.w/2+rect.h/2};
    }
    void move(){
        //mise a jour de la vitesse
        vx+=ax;
        vy+=ay;
        if(vx>game->max_speed) vx=game->max_speed;
        else if(vx<-game->max_speed) vx=-game->max_speed;
        if(vy>game->max_speed) vy=game->max_speed;
        else if(vy<-game->max_speed) vy=-game->max_speed;
        //deplacement des points
        pos.x+=vx;
        pos.y+=vy;

        pos.x=adjust(pos.x,game->width);
        pos.y=adjust(pos.y,game->height);

        //Mise a jour de l'acceleration
        if(ax==0 || (ax<VOID_RESISTANCE && ax>-VOID_RESISTANCE)){
            ax=0;
            if(game->obstacle_slowing){
                if(vx<VOID_RESISTANCE && vx>-VOID_RESISTANCE){
                    vx=0;
                }
                else
                    vx>0?vx-=VOID_RESISTANCE:vx+=VOID_RESISTANCE;
            }
        }
        else if(ax<0)
            ax+=VOID_RESISTANCE;
        else
            ax-=VOID_RESISTANCE;
        if(ay==0 || (ay<VOID_RESISTANCE && ay >-VOID_RESISTANCE)){
            ay=0;
            if(game->obstacle_slowing){
                if(vy<VOID_RESISTANCE && vy>-VOID_RESISTANCE){
                    vy=0;
                }
                else
                    vy>0?vy-=VOID_RESISTANCE:vy+=VOID_RESISTANCE;
            }
        }
        else if(ay<0)
            ay+=VOID_RESISTANCE;
        else
            ay-=VOID_RESISTANCE;
    }
private:
    Parameters *game;
    int npoints = 8;
    SDL_Point points[8];
    double ax,ay,vx,vy;
    void generate(){
        vx=vy=ax=ay=0;
        int step=0;
        int radius=size*10;
        for(int k=0;k<8;k++){
            int x = rand() % (radius-1);
            int y=(int)std::sqrt(radius*radius - x*x);
            if(step>5){
                x=-x;
                if(points[4].y>points[5].y){
                    SDL_Point tmp = points[4];
                    points[4]=points[5];
                    points[5]=tmp;
                }
            }
            else if(step>3){
                y=-y;
                x=-x;
                if(points[2].y<points[3].y){
                    SDL_Point tmp = points[2];
                    points[2] =points[3];
                    points[3]=tmp;
                }
            }
            else if(step>1){
                y=-y;
                if(points[0].y<points[1].y){
                    SDL_Point tmp= points[0];
                    points[0]= points[1];
                    points[1]=tmp;
                }
            }
            points[k]={x,y};
            step++;
        }
        if(points[6].y>points[7].y){
            SDL_Point tmp=points[6];
            points[6]=points[7];
            points[7]=tmp;
        }
    }

    void init_movement(){
        double r=(double)rand()/RAND_MAX;
        ax=r*(game->initial_acc_max-game->initial_acc_min);
        if(rand()%2)
            ax=-ax;
        r=(double)rand()/RAND_MAX;
        ay=r*(game->initial_acc_max-game->initial_acc_min);
        if(rand()%2)
            ay=-ay;
    }
};