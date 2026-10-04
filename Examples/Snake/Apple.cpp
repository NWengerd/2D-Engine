#include "Apple.hpp"
#include "SnakeGame.hpp"
#include <cstdlib>
#include <ctime>

Apple::Apple(Game* g) : game(g)
{
}

void Apple::spawn()
{
	// Set seed for random generation
	std::srand(std::time({}));
	bool flag = true;
	
	// Attempt to spawn apple
	while (flag)
	{
		// Assume success
		flag = false;

		pos.x = (rand() % 16) * 50;
		pos.y = (rand() % 12) * 50;

		for (auto i = game->snake.body.begin(); i != game->snake.body.end(); i++)
		{
			if (i->newPos->x == pos.x && i->newPos->y == pos.y)
			{
				// Retry rand
				flag = true;
				break;
			}

		}
	}
}


void Apple::render()
{
	game->engine.renderer.square(pos.x, pos.y, 50, 1.0f, 0, 0);
}


bool Apple::checkColl()
{
	if (pos.x == game->snake.currPos.x && pos.y == game->snake.currPos.y)
	{
		return true;
	}
	else { return false; }
}