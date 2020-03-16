#include <SDL2/SDL.h>
#include "../include/obstacle.h"
#include <ctime>
#include "../include/parameters.h"
#include "../include/ship.h"
#include <iostream>

int width;
int height;
SDL_Window *window;
SDL_Renderer *renderer;

void draw(SDL_Renderer *renderer, Obstacle obstacles[], int nob, Ship player)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	for (int k = 0; k < nob; k++)
	{
		obstacles[k].draw(renderer);
		obstacles[k].move();
	}
	if(!player.hurt)
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	else
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	player.draw(renderer);
}

int main(int argc, char **argv)
{
	Parameters game = Parameters();
	int prevTicks = 0;
	std::srand(std::time(0));
	std::srand((unsigned int)rand());
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		return 1;
	}

	window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, game.width, game.height,
							  SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
	SDL_SetWindowResizable(window, SDL_TRUE);
	renderer = SDL_CreateRenderer(window, -1,
								  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_GetRendererOutputSize(renderer, &width, &height);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);

	Obstacle obstacles[game.start_obstacles];
	int nob = 0;
	//on genere des obstacles
	for (; nob < game.start_obstacles; nob++)
	{
		obstacles[nob] = Obstacle(nob * 80 + 50, 150, 1 + rand() % 3, &game);
	}

	Ship player(game.width / 2, game.height / 2, &game);

	bool quit = false;
	prevTicks = SDL_GetTicks();
	int ticks = 0;
	int ticks_collision_ship=0;
	while (!quit)
	{
		//limiting the rendering to a certain amount of frames per second
		if (SDL_GetTicks() - prevTicks > 1000 / game.cst_fps)
		{
			++ticks %= game.cst_fps;
			//ship movement
			player.move();
            SDL_FPoint shipPoints[3];
		    player.getPoints(shipPoints);
			if(ticks_collision_ship==0){
				player.hurt=false;
		    for (int i=0; i<nob; i++){
			    	if (obstacles[i].checkObjectCollision(shipPoints,player.pos,3)) {
				    	quit = (player.respawn()<=0);
						ticks_collision_ship=game.invincibility_ticks;
						player.hurt=true;
			    	}
		    }
			}
			else{
				ticks_collision_ship--;
			}
			player.applyEvents();
			prevTicks = SDL_GetTicks();
			draw(renderer, obstacles, nob, player);
			SDL_RenderPresent(renderer);
			if (ticks % game.bullet_ticks_cooldown == 0)
			{
				player.shoot();
			}
		}
		int count = 0;
			SDL_Event event;
			//limiting the loop to a certain number of events per tick
			while (count++ < game.events_per_tick && !quit && SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					// touche clavier enfoncee
					case SDLK_LEFT:
						game.left = true;
						break;
					case SDLK_RIGHT:
						game.right = true;
						break;
					case SDLK_DOWN:
						game.back = true;
						break;
					case SDLK_UP:
						game.forward = true;
						break;
					case SDLK_SPACE:
						game.shoot = true;
						break;
					case SDLK_ESCAPE:
						quit = true;
						break;
					default:
						count--;
						break;
					}
					break;
				case SDL_KEYUP:
					switch (event.key.keysym.sym)
					{
					//touche clavier relachee
					case SDLK_LEFT:
						game.left = false;
						break;
					case SDLK_RIGHT:
						game.right = false;
						break;
					case SDLK_DOWN:
						game.back = false;
						break;
					case SDLK_UP:
						game.forward = false;
						break;
					case SDLK_SPACE:
						game.shoot = false;
						break;
					default:
						count--;
						break;
					}
					break;
				case SDL_MOUSEMOTION: /*x += event.motion.xrel;*/
					break;
				case SDL_MOUSEBUTTONDOWN:
					break;
				case SDL_WINDOWEVENT:
					if (event.window.event == SDL_WINDOWEVENT_RESIZED)
					{
						game.width = event.window.data1;
						game.height = event.window.data2;
					}
					break;
				default:
					count--;
					break;
				}
			}
	}
	if (renderer)
		SDL_DestroyRenderer(renderer);
	if (window)
		SDL_DestroyWindow(window);
	SDL_Quit();
}
