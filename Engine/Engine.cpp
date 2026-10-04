#include "Engine.hpp"
#include <GLFW\glfw3.h>
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")

Application::Application() : renderer(windowManager.width, windowManager.height, windowManager.window)
{
}

Application::~Application()
{
	glfwTerminate();
}

void Application::run()
{

}

GLFWwindow* Application::getWindow()
{
	return windowManager.window;
}

