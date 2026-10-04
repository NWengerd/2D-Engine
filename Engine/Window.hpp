#ifndef WINDOW
#define  WINDOW

#include <string>
#include <glad/glad.h>

struct GLFWwindow;

class Window
{
private:
	

public:
	Window();

	int width = 800;
	int height = 600;

	GLFWwindow* window = nullptr;
	
	bool createWindow();
};

void resizeFramebuffer(GLFWwindow*, int width, int length);
#endif