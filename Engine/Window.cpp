#include "Window.hpp"
#include <iostream>
#include <GLFW/glfw3.h>

Window::Window()
{
	createWindow();
}

// FIXME: Add customizable window size and name
// FIXME: Perhaps make context creation seperate, and go through window class itself
bool Window::createWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// Create window and set it as context for OpenGL 
	this->window = glfwCreateWindow(this->width, this->height, "LearnOpenGL", NULL, NULL);
	if (this->window == NULL)
	{
		// Terminate program if process failed
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return 0;
	}
	glfwMakeContextCurrent(this->window);

	// Initialize GLAD before we call any OpenGL functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) // Works only after OpenGL context creation above
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return 0;
	}

	// Accomodate window resizing
	glViewport(0, 0, this->width, this->height);
	glfwSetFramebufferSizeCallback(this->window, resizeFramebuffer);
}


// Window resize callback, is called everytime window is resized
void resizeFramebuffer(GLFWwindow*, int width, int height)
{
	glViewport(0, 0, width, height);
}

