#include <SDL2/SDL.h>
#include "../include/obstacle.h"
#include <ctime>
#include "../include/game.h"
#include "../include/ship.h"
#include <iostream>
#include <list>

int main(int argc, char **argv)
{
	Game game = Game();
	game.init();
	game.loop();
}
