#include "../include/turret.h"
#include <iostream>

void Turret::move()
{
    if(active){
    angle = angle > 360 ? angle - 360 : angle < 0 ? angle + 360 : angle;
    pos.x += vx;
    pos.y += vy;
    pos.x = adjust(pos.x, game->width);
    pos.y = adjust(pos.y, game->height);
    SDL_FPoint player = game->getPlayerPosition();
    SDL_FPoint dO = {points[2].x - pos.x, points[2].y - pos.y};
    SDL_FPoint dP = {player.x - pos.x, player.y - pos.y};
    double a = atan2(dO.y, dO.x);
    double b = atan2(dP.y, dP.x);
    double diff = a - b;
    angle = -diff + M_PI_2;
    if (ticksBeforeShot == 0)
    {
        ticksBeforeShot = minTicks + rand() % maxTicks;
        bullet b = bullet(pos, angle, game);
        bullets.emplace_front(b);
    }
    ticksBeforeShot--;
    }
    updateBullets();
}

void Turret::draw(SDL_Renderer *renderer)
{
    drawBullets(renderer);
    if(active){
    Uint8 r, g, b, a;
    if (SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a) < 0)
    {
        std::cout << "Turret.draw: SDL_GetRenderDrawColor: " << SDL_GetError() << std::endl;
        r = g = a = 255;
    }
    SDL_FPoint tmp[npoints];
    for (int i = 0; i < npoints; i++)
    {
        tmp[i].x = points[i].x * cosf(angle) - points[i].y * sinf(angle);
        tmp[i].y = points[i].x * sinf(angle) + points[i].y * cosf(angle);
    }
    add(npoints, tmp, pos);
    SDL_SetRenderDrawColor(renderer, 204, 255, 0, 255);
    SDL_RenderDrawLinesF(renderer, tmp, npoints);
    SDL_RenderDrawLineF(renderer, tmp[npoints - 1].x, tmp[npoints - 1].y, tmp[0].x, tmp[0].y);
    SDL_RenderDrawLineF(renderer, pos.x, pos.y, tmp[2].x, tmp[2].y);
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    }
}

void Turret::generate()
{
    npoints = 8;
    radius = 20;
    float angl = 0;
    for (int k = 0; k < npoints; k++)
    {
        float x = radius * cosf(angl),
              y = radius * sinf(angl);
        points[k] = {x, y};
        angl += 2 * M_PI / npoints;
    }
}

bool Turret::checkObjectCollision(SDL_FPoint objPoints[], SDL_FPoint objPos, int n)
{
    if(!active) return false;
    for (int i = 0; i < n; i++)
    {
        if (objPoints[i].x >= pos.x - radius && objPoints[i].x <= pos.x + radius &&
            objPoints[i].y >= pos.y - radius && objPoints[i].y <= pos.y + radius)
            return true;
    }
    return false;
}

void Turret::init_movement()
{
    vx = rand() % max_inertia;
    vy = rand() % max_inertia;
}

void Turret::drawBullets(SDL_Renderer *renderer)
{
    for (auto b = bullets.begin(); b != bullets.end(); b++)
    {
        if (!b->remove)
            b->draw(renderer);
    }
}

void Turret::updateBullets()
{
    bool first = true;
    std::_Fwd_list_iterator<bullet> prev = bullets.begin();
    auto i = bullets.begin();
    while (i != bullets.end())
    {
        if (i->remove)
        {
            i++;
            if (!first)
            {
                bullets.erase_after(prev);
            }
            else
            {
                bullets.pop_front();
                prev = bullets.begin();
            }
            //std::cout<<"peeeeeew~"<<std::endl;
        }
        else
        {
            i->move();
            if (!first)
                prev++;
            else
                first = false;
            i++;
        }
    }
}

std::_Fwd_list_iterator<bullet> Turret::getBulletsBegin() {
    return bullets.begin();
}

std::_Fwd_list_iterator<bullet> Turret::getBulletsEnd() {
    return bullets.end();
}