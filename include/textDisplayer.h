#ifndef TEXTDISPLAYER_H
#define TEXTDISPLAYER_H

#include <string>
#include <iostream>
#include <SDL.h>

void displayText(SDL_Renderer *renderer, float x, float y, std::string text, int size);
void displaySymbol(SDL_Renderer *renderer, float x, float y, int c, int size);


#endif