#ifndef APPLE
#define APPLE

#include "snake.hpp"

class Game;

class Apple
{
private:
	// Access to game state
	Game* game;
	Pos pos = { -100, -100 };

public:
	Apple(Game* g);
	void spawn();
	void render();
	bool checkColl();
};


#endif