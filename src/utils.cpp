#include "../include/utils.h"

double adjust(double x, int threshold)
{
    return x >= threshold ? x - threshold : x <= 0 ? x + threshold : x;
}

void add(int n, SDL_Point tab[], SDL_Point p)
{
    for (int k = 0; k < n; k++)
    {
        tab[k].x += p.x;
        tab[k].y += p.y;
    }
}

void add(int n, SDL_FPoint tab[], SDL_FPoint p)
{
    for (int k = 0; k < n; k++)
    {
        tab[k].x += p.x;
        tab[k].y += p.y;
    }
}

void sub(int n, SDL_Point tab[], SDL_Point p)
{
    for (int k = 0; k < n; k++)
    {
        tab[k].x -= p.x;
        tab[k].y -= p.y;
    }
}

SDL_FPoint operator+(SDL_FPoint a, SDL_FPoint b)
{
    SDL_FPoint c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    return c;
}

SDL_FPoint operator-(SDL_FPoint a, SDL_FPoint b)
{
    SDL_FPoint c;
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    return c;
}