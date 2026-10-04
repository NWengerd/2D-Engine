#include "Snake.hpp"
#include <GLFW/glfw3.h>

SnakeHead::SnakeHead(Application* e) : engine(e)
{
	currPos = { 0,0 };
	prevPos = { 0,0 };
	prevTime = 0.0f;
}

void SnakeHead::render()
{
	engine->renderer.square(currPos.x, currPos.y, 50, 0, 1.0f, 0);
}


void SnakeHead::update(int& dir)
{
	// Move snake if 1.5 seconds have elapsed
	if (glfwGetTime() - prevTime >= 0.5f)
	{
		// Update body positions back to front for technical reasons
		for (auto i = body.rbegin(); i != body.rend(); i++) { i->update(); }
		// Update previous position
		prevPos = currPos;
		// Reset timer
		prevTime = glfwGetTime();

		if (dir == 1)
			currPos.x += 50;
		else if (dir == -1)
			currPos.x -= 50;
		else if (dir == 2)
			currPos.y += 50;
		else if (dir == -2)
			currPos.y -= 50;
		else { /* do nothing*/ }

	}

	// Check if in window bounds
	if (checkBounds())
	{
		// Reset
		body.clear();
		currPos = { 0,0 };
		dir = 0;
	}

	// Check if head is intersecting body, and render body
	for (auto i = body.begin(); i != body.end(); i++)
	{
		if (checkColl(i->newPos))
		{
			// Reset
			body.clear();
			currPos = { 0,0 };
			dir = 0;
			break;
		}
		i->render();
	}

	render();
	
}


void SnakeHead::createBody()
{
	if (body.empty()) 
	{
		// If first body piece, give new body prevPos of head
		body.push_back(SnakeBody(&this->prevPos, engine));
	}
	else
	{
		// If not first body piece, give new body prevPos of last body piece in list
		auto a = body.end();
		a--;
		body.push_back(SnakeBody(&(a->prevPos), engine));
	}
	
}

// Checks if collision between snakehead and given object position
bool SnakeHead::checkColl(const Pos* otherPos)
{
	if (this->currPos.x == otherPos->x && this->currPos.y == otherPos->y)
	{
		return true;
	}
	else { return false; }
}


bool SnakeHead::checkBounds()
{
	if (currPos.x >= 800 || currPos.x < 0 || currPos.y >= 600 || currPos.y < 0)
	{
		return true;
	}
	else { return false; }
}


SnakeBody::SnakeBody(Pos* pass, Application* e) : newPos(pass), engine(e)
{
}


void SnakeBody::render()
{
	engine->renderer.square(newPos->x, newPos->y, 50, 0, 0.75f, 0);
}


void SnakeBody::update()
{
	prevPos = *newPos;
}