#ifndef MENU_H
#define MENU_H
#include <SDL2/SDL.h>
#include <iostream>
#include "parameters.h"
#include "textDisplayer.h"
#include <string>
#include <fstream>
class Menu
{
private:
    SDL_Texture* logo;
    SDL_Texture* play;
    Parameters* game;
    Uint8 playAlpha;
    int width1,height1,width2,height2;
    bool decrAlpha=true;
    void init();
    int score, highScore;
public:
    Menu(Parameters* param){
        game=param;
        playAlpha=255;
        init();
    }
    ~Menu(){
        SDL_DestroyTexture(logo);
    }
    void draw(int score);
};

#endif