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
    std::ifstream file(game->fileScore.c_str());
    if(file){
        std::string Hscore;
        getline(file,Hscore);
        highScore=std::stoi(Hscore);
    }
}

void Menu::draw(int score){
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
        playAlpha += 3;
    SDL_SetTextureAlphaMod(play, playAlpha);
    SDL_RenderCopy(game->renderer, play, NULL, &dstPlay);
        SDL_SetRenderDrawColor(game->renderer, 200, 200, 200, 255);
        std::string str_score = "Previous score: " + std::to_string(score);
        displayText(game->renderer, game->width/2-(18*str_score.size())/2, game->height/2, str_score, 1);
        if(score>highScore){
            std::ofstream ofs;
            ofs.open(game->fileScore.c_str(), std::ofstream::out | std::ofstream::trunc);
            std::string sScore = std::to_string(score); 
            ofs.write(sScore.c_str(),strlen(sScore.c_str()));
            ofs.close();
            highScore=score;
        }
        std::string str_HScore = "Local High Score: "+std::to_string(highScore);
        displayText(game->renderer,game->width/2 -(18*str_HScore.size())/2,50+game->height/2,str_HScore,1);
    SDL_RenderPresent(game->renderer);
}
