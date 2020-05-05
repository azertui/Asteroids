#include <SDL.h>
#include "obstacle.h"
#include <ctime>
#include "game.h"
#include "ship.h"
#include <iostream>
#include <list>

int main()
{
	Game game = Game();
	game.init();
	game.loop();
}
