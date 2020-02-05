#include <SDL2/SDL.h>
#include "../include/obstacle.h"
#include <ctime>

int width;
int height;
SDL_Window* window;
SDL_Renderer* renderer;

void draw(SDL_Renderer* renderer, Obstacle obstacles[],int nob)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255,255,0,255);
	for(int k=0;k<nob;k++)
		obstacles[k].draw(renderer);

	int x,y;
	if ( SDL_GetMouseState(&x,&y) & SDL_BUTTON(SDL_BUTTON_LEFT) ) // one & it is for bits AND
	{
		SDL_RenderDrawLine(renderer,width/2,height/2,x,y );
	}
}



int main(int argc, char** argv)
{
	std::srand(std::time(0));
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		return 1;
	}

	window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 600,
						  SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI);
	renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

	SDL_GetRendererOutputSize(renderer, &width, &height);
	SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_ADD);

	Obstacle obstacles[10];
		int nob =0;
		//on genere un ob pour les tests
		for(;nob<10;nob++){
			obstacles[nob]= Obstacle(nob*80+50,150,1+rand()%3);
		}

	bool quit = false;
	while (!quit)
	{

		SDL_Event event;
		while (!quit && SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					// touche clavier
					case SDLK_LEFT: ; break;
					case SDLK_RIGHT: ; break;
					case SDLK_ESCAPE: quit = true; break;
					default: break;
				}
				break;
			case SDL_MOUSEMOTION:	/*x += event.motion.xrel;*/	break;
			case SDL_MOUSEBUTTONDOWN:
				printf("mouse click %d %d \n", event.button.x,event.button.y);
				break;
			default: break;
			}
		}
		draw(renderer,obstacles,nob);
		SDL_RenderPresent(renderer);
	}
	if(renderer)
		SDL_DestroyRenderer(renderer);
	if(window)
		SDL_DestroyWindow(window);
	SDL_Quit();

}
