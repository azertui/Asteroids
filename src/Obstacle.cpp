
#include <cmath>

#include "Obstacle.h"

Obstacle::Obstacle() {
    this->size = 0;
}

Obstacle::Obstacle(int x, int y, int s) {
    this->pos  = { x, y };
    this->size = s;
    generate();
}

void Obstacle::draw(SDL_Renderer * renderer) {
    if(this->size > 0)
        SDL_RenderDrawLines(renderer, points, 8);
    SDL_RenderDrawLine(renderer, points[7].x, points[7].y, points[0].x,
                       points[0].y);
}

void Obstacle::generate() {
    int step   = 0;
    int radius = this->size * 20;
    for(int k = 0; k < 8; k++) {
        int x = rand() % (radius - 1);
        int y = (int) std::sqrt(radius * radius - x * x);
        if(step > 5) {
            x = -x;
            if(points[4].y > points[5].y) {
                SDL_Point tmp = points[4];
                points[4]     = points[5];
                points[5]     = tmp;
            }
        } else if(step > 3) {
            y = -y;
            x = -x;
            if(points[2].y < points[3].y) {
                SDL_Point tmp = points[2];
                points[2]     = points[3];
                points[3]     = tmp;
            }
        } else if(step > 1) {
            y = -y;
            if(points[0].y < points[1].y) {
                SDL_Point tmp = points[0];
                points[0]     = points[1];
                points[1]     = tmp;
            }
        }
        points[k] = { this->pos.x + x, this->pos.y + y };
        step++;
    }
    if(points[6].y > points[7].y) {
        SDL_Point tmp = points[6];
        points[6]     = points[7];
        points[7]     = tmp;
    }
}