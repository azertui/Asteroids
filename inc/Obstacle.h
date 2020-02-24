
#ifndef _OBSTACLE_
#define _OBSTACLE_

#include <SDL.h>

class Obstacle {
  public:
    SDL_Point pos;
    int size;

    Obstacle();
    Obstacle(int x, int y, int s);
    void draw(SDL_Renderer * renderer);

  private:
    SDL_Point points[8];
    void generate();
};

#endif