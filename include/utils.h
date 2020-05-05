#include <SDL.h>

double adjust(double,int);
void add(int n,SDL_Point tab[], SDL_Point p);
void add(int n,SDL_FPoint tab[], SDL_FPoint p);
void sub(int n,SDL_Point tab[], SDL_Point p);
SDL_FPoint operator+(SDL_FPoint a, SDL_FPoint const& b);
SDL_FPoint operator-(SDL_FPoint a, SDL_FPoint const& b);
SDL_FPoint& operator+=(SDL_FPoint& a, SDL_FPoint const& b);
SDL_FPoint& operator-=(SDL_FPoint& a, SDL_FPoint const& b);
void sub(int n,SDL_FPoint tab[], SDL_FPoint p);

bool segmentsIntersect(SDL_FPoint A, SDL_FPoint B, 
                       SDL_FPoint C, SDL_FPoint D);
float det(SDL_FPoint A, SDL_FPoint B, SDL_FPoint C);

double bornes(double n, double min, double max);