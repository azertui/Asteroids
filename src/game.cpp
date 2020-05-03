#include "../include/game.h"
#include <iostream>

Game::Game()
{
}

int Game::init()
{
	prevTicks = 0;
	std::srand(std::time(0));
	std::srand((unsigned int)rand());
	ships = std::list<SpaceShip *>();
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		return 1;
	}

	parameters.window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, parameters.width, parameters.height,
										 SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
	SDL_SetWindowResizable(parameters.window, SDL_TRUE);
	parameters.renderer = SDL_CreateRenderer(parameters.window, -1,
											 SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_GetRendererOutputSize(parameters.renderer, &(parameters.width), &(parameters.height));
	SDL_SetRenderDrawBlendMode(parameters.renderer, SDL_BLENDMODE_ADD);

	player = Ship(parameters.width / 2, parameters.height / 2, &parameters);
	parameters.setPlayerPosition(player.getPosition());
	quit = false;
	prevTicks = SDL_GetTicks();
	ticks = 0;
	ticks_collision_ship = 0;
	score = 0;
	level = 0;
	return 0;
}

void Game::start(){
	Obstacle *obs;
	int nob = 0;
	//on genere des obstacles
	for (; nob < parameters.start_obstacles; nob++)
	{
		obs = getRandomObstacle(nob * 80 + 50, 150, 2 + rand() % 2, &parameters);
		obstacles.emplace_front(obs);
	}
	SpaceShip *sh;
	int nos = 0;
	for (; nos < parameters.start_ships; nos++)
	{
		sh = getRandomSpaceShip(nos * 80 + 50, 600, &parameters);
		ships.emplace_front(sh);
	}
}

void Game::loop()
{
	while (!quit)
	{
		if (obstacles.begin() == obstacles.end() && ships.begin() == ships.end()) {
			level++;
			start();
		}
		//limiting the rendering to a certain amount of frames per second
		if (SDL_GetTicks() - prevTicks > 1000 / parameters.cst_fps)
		{
			++ticks %= parameters.cst_fps;
			//ship movement
			player.move();
			SDL_FPoint shipPoints[3];
			player.getPoints(shipPoints);
			if (ticks_collision_ship == 0)
			{
				player.hurt = false;
				for (auto obs = obstacles.begin(); obs != obstacles.end(); ++obs)
				{
					if(player.hurt) break;
					if ((*obs)->checkObjectCollision(shipPoints, player.pos, 3))
					{
						quit = (player.respawn() <= 0);
						ticks_collision_ship = parameters.invincibility_ticks;
						player.hurt = true;
					}
				}
			}
			else
			{
				ticks_collision_ship--;
			}
			// obstacles-bullets collisions
			bullets_begin = player.getBulletsBegin();
			bullets_end = player.getBulletsEnd();
			SDL_FPoint bullet_points[2];
			std::list<Obstacle *> new_obstacles;
			auto obs = obstacles.begin();
			bool collision_detected;
			while (obs != obstacles.end())
			{
				collision_detected = false;
				for (auto b = bullets_begin; b != bullets_end; b++)
				{
					if (!b->remove)
					{
						b->getBoundingBox(bullet_points);
						if ((*obs)->checkObjectCollision(bullet_points, bullet_points[0], 2))
						{
							collision_detected = true;
							b->remove = true;
							score += (*obs)->getScore();
							new_obstacles = (*obs)->split();
							if (!new_obstacles.empty())
								obstacles.splice(obstacles.begin(), new_obstacles);
							obs = obstacles.erase(obs);
							break;
						}
					}
				}
				if (!collision_detected)
					obs++;
			}
			auto sh = ships.begin();
			while (sh != ships.end())
			{
				collision_detected = false;
				if ((*sh)->isInactive())
				{
					collision_detected = true;
					sh = ships.erase(sh);
					break;
				}
				for (auto b = player.getBulletsBegin(); b != player.getBulletsEnd(); b++)
				{
					if (!b->remove)
					{
						b->getBoundingBox(bullet_points);
						if ((*sh)->checkObjectCollision(bullet_points, bullet_points[0], 2))
						{
							(*sh)->setInactive();
							b->remove = true;
							if ((*sh)->isInactive())
							{
								collision_detected = true;
								score += (*sh)->score;
								sh = ships.erase(sh);
								break;
							}
						}
					}
				}
				if (!collision_detected)
				{
					for (auto be = (*sh)->getBulletsBegin(); be != (*sh)->getBulletsEnd(); be++)
					{
						be->getBoundingBox(bullet_points);
						if (!player.hurt && player.checkObjectCollision(bullet_points, bullet_points[0], 2))
						{
							be->remove = true;
							quit = (player.respawn() <= 0);
							ticks_collision_ship = parameters.invincibility_ticks;
							player.hurt = true;
						}
					}
					sh++;
				}
			}

			player.applyEvents();
			prevTicks = SDL_GetTicks();
			draw();
			SDL_RenderPresent(parameters.renderer);
			if (ticks % parameters.bullet_ticks_cooldown == 0)
			{
				player.shoot();
			}
		}
		int count = 0;
		SDL_Event event;
		//limiting the loop to a certain number of events per tick
		while (count++ < parameters.events_per_tick && !quit && SDL_PollEvent(&event))
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
					parameters.left = true;
					break;
				case SDLK_RIGHT:
					parameters.right = true;
					break;
				case SDLK_DOWN:
					parameters.back = true;
					break;
				case SDLK_UP:
					parameters.forward = true;
					break;
				case SDLK_SPACE:
					parameters.shoot = true;
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
					parameters.left = false;
					break;
				case SDLK_RIGHT:
					parameters.right = false;
					break;
				case SDLK_DOWN:
					parameters.back = false;
					break;
				case SDLK_UP:
					parameters.forward = false;
					break;
				case SDLK_SPACE:
					parameters.shoot = false;
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
					parameters.width = event.window.data1;
					parameters.height = event.window.data2;
				}
				break;
			default:
				count--;
				break;
			}
		}
	}
	if (parameters.renderer)
		SDL_DestroyRenderer(parameters.renderer);
	if (parameters.window)
		SDL_DestroyWindow(parameters.window);
	SDL_Quit();
}

Parameters *Game::getParameters()
{
	return &parameters;
}

void Game::draw()
{
	SDL_SetRenderDrawColor(parameters.renderer, 0, 0, 0, 255);
	SDL_RenderClear(parameters.renderer);
	SDL_SetRenderDrawColor(parameters.renderer, 255, 255, 0, 255);
	for (auto obs = obstacles.begin(); obs != obstacles.end(); ++obs)
	{
		(*obs)->draw(parameters.renderer);
		(*obs)->move();
	}
	for (auto sh = ships.begin(); sh != ships.end(); ++sh)
	{
		(*sh)->draw(parameters.renderer);
		(*sh)->move();
	}
	// display score test 
	std::string str_score = std::to_string(score);
	displayText(parameters.renderer, 20, parameters.cst_ssize * 4, str_score, 1);
	if (!player.hurt)
		SDL_SetRenderDrawColor(parameters.renderer, 1, 255, 195, 255);
	else
		SDL_SetRenderDrawColor(parameters.renderer, 242, 26, 29, 255);
	player.draw(parameters.renderer);
}