#include "SnakeGame.hpp"
#include <GLFW\glfw3.h>


Game::Game() : snake(&engine), apple(this)
{
}

void Game::draw()
{
	apple.spawn();
	// Main loop
	while (!glfwWindowShouldClose(engine.getWindow()))
	{
		processInput();
		createGrid();
		updateSnake();
		updateApple();

		engine.renderer.endFrame();
	}
}


void Game::updateApple()
{
	apple.render();
	if (apple.checkColl())
	{
		snake.createBody();
		apple.spawn();
	}
}


void Game::updateSnake()
{
	snake.update(moveDir);
}

// process user input to move snake
void Game::processInput()
{
	
	// 1 == right, -1 == left, 2 == up, -2 == down
	if (glfwGetKey(engine.getWindow(), GLFW_KEY_UP) == GLFW_PRESS)
		moveDir = 2;
	else if (glfwGetKey(engine.getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
		moveDir = -2;
	else if (glfwGetKey(engine.getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
		moveDir = 1;
	else if (glfwGetKey(engine.getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
		moveDir = -1;
	else if (glfwGetKey(engine.getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
		snake.createBody();
}


void Game::createGrid()
{
	float temp = 0.15f;
	// Create Grid
	for (int i = 0; i < 12; i++)
	{
		//Y-axis shift
		for (int j = 0; j < 16; j++)
		{
			temp *= -1;

			// X-axis shift
			engine.renderer.square(j * 50, i * 50, 50, 0.3f + temp, 0.3f + temp, 0.3f + temp);
		}
		temp *= -1;
	}
}