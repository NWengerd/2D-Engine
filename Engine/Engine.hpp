#ifndef ENGINE
#define ENGINE

#include "Window.hpp"
#include "Renderer.hpp"

class Application
{
private:
	
	Window windowManager;
	

public:
	Application();
	~Application();
	Renderer renderer;
	GLFWwindow* getWindow();
	void run();
};

#endif