#include "../include/menu.h"

void Menu::init(){
    SDL_Surface* img= SDL_LoadBMP("data/asteroid.bmp");
    SDL_Surface* img2 = SDL_LoadBMP("data/enter.bmp");
    if(img==NULL){
        std::cout << "Erreur de chargement du logo: "<<SDL_GetError()<<std::endl;  
        return;
    }
    if(img2==NULL){
        std::cout << "Erreur de chargement de l'image enter"<<SDL_GetError()<<std::endl;
        return;
    }
    logo = SDL_CreateTextureFromSurface(game->renderer, img);
    play = SDL_CreateTextureFromSurface(game->renderer,img2);
    SDL_FreeSurface(img);
    SDL_FreeSurface(img2);
    
    SDL_QueryTexture(logo, NULL, NULL, &width1, &height1);
    SDL_QueryTexture(play, NULL, NULL, &width2, &height2);
}

void Menu::draw(){
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);
    SDL_Rect dst = {(game->width/2)-width1/2,0,width1,height1};
    SDL_Rect dstPlay = {(game->width/2)-width2/2,3*game->height/4-height2,width2,height2};
    SDL_RenderCopy(game->renderer,logo,NULL,&dst);
    if(playAlpha==0){
        decrAlpha=false;
    }else if(playAlpha==255){
        decrAlpha=true;
    }
    if(decrAlpha)
        playAlpha-=3;
    else
        playAlpha+=3;
    SDL_SetTextureAlphaMod(play,playAlpha);
    SDL_RenderCopy(game->renderer,play,NULL,&dstPlay);
    SDL_RenderPresent(game->renderer);
}