#include <SDL2/SDL.h>

double adjust(double,int);
void add(int n,SDL_Point tab[], SDL_Point p);
void add(int n,SDL_FPoint tab[], SDL_FPoint p);
void sub(int n,SDL_Point tab[], SDL_Point p);
SDL_FPoint operator+(SDL_FPoint a, SDL_FPoint b);
SDL_FPoint operator-(SDL_FPoint a, SDL_FPoint b);