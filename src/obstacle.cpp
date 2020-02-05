#include <SDL2/SDL.h>
#include <cmath>

class Obstacle
{
public:
    SDL_Point pos;
    int size;
    Obstacle(){
        size=0;
    }
    Obstacle(int x, int y, int s)
    {
        pos = {x, y};
        size = s;
        generate();
    }
    void draw(SDL_Renderer *renderer){
        if(size>0)
            SDL_RenderDrawLines(renderer,points,8);
            SDL_RenderDrawLine(renderer,points[7].x,points[7].y,points[0].x,points[0].y);
    }
private:
    SDL_Point points[8];
    void generate(){
        int step=0;
        int radius=size*20;
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
            points[k]={pos.x+x,pos.y+y};
            step++;
        }
        if(points[6].y>points[7].y){
            SDL_Point tmp=points[6];
            points[6]=points[7];
            points[7]=tmp;
        }
    }
};