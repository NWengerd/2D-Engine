#ifndef SNAKEGAME
#define SNAKEGAME

#include "../../Engine/Engine.hpp"
#include "Snake.hpp"
#include "Apple.hpp"

class Game
{
private:
	int moveDir = 0;
	
	void createGrid();
	void updateSnake();
	void updateApple();
	void processInput();

public:
	Application engine;
	SnakeHead snake;
	Apple apple;
	
	Game();
	void draw();

	

};
#endif