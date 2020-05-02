#ifndef TEXTDISPLAYER_H
#define TEXTDISPLAYER_H

#include <string>
#include <iostream>
#include <SDL2/SDL.h>

void displayText(SDL_Renderer *renderer, float x, float y, std::string text, float size);
void displaySymbol(SDL_Renderer *renderer, float x, float y, int c, float size);


#endif