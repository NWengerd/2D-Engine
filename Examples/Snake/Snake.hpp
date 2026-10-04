#ifndef SNAKE
#define SNAKE

#include "../../Engine/Engine.hpp"
#include <list>

struct Pos
{
	int x, y;
};


class SnakeBody
{
private:
	Application* engine;
	

public:
	SnakeBody(Pos* pass, Application* e);
	void render();
	void update();

	const Pos* newPos;
	Pos prevPos = { -100,-100 };
};


class SnakeHead
{
private:
	
	Application* engine;
	// Linked list to hold snake objects
	

	float prevTime;

public:
	std::list<SnakeBody> body;
	
	SnakeHead(Application* e);

	Pos currPos;
	Pos prevPos;

	void render();
	void update(int& dir);
	void createBody();
	bool checkColl(const Pos* otherPos);
	bool checkBounds();

};

#endif SNAKE