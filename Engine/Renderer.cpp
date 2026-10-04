#include "Renderer.hpp"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


Renderer::Renderer(int width, int height, GLFWwindow* win) : squareShader("C:/Users/naten/Desktop/OpenGL/2D_Engine/Engine/VertexShader.vs", "C:/Users/naten/Desktop/OpenGL/2D_Engine/Engine/FragmentShader.fs")
{
	// Main shader
	// FIXME: More shaders will be necessary in future
	squareShader.use();
	
	this->window = win;
	
	getLocs();
	squareInit();
	createProjection(width, height);
}

// Get uniform location for all shader uniforms
void Renderer::getLocs()
{
	squareLocs.proj = glGetUniformLocation(squareShader.ID, "projection");
	squareLocs.view = glGetUniformLocation(squareShader.ID, "view");
	squareLocs.model = glGetUniformLocation(squareShader.ID, "model");
	squareLocs.color = glGetUniformLocation(squareShader.ID, "aColor");
}

void Renderer::squareInit()
{
	glGenVertexArrays(1, &squareVAO);
	// Create VBO
	glGenBuffers(1, &squareVBO);
	// Create EBO
	glGenBuffers(1, &squareEBO);


	// Bind VAO
	glBindVertexArray(squareVAO);
	//Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, squareVBO);
	// Send vertex data and tell VBO how to interpret
	glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);
	// Bind EBO and send indice data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squareIndices), squareIndices, GL_STATIC_DRAW);

	// Bind to vertexshader location and give size and step, assuming only x,y,z
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

//Create and send projection and view matrix
void Renderer::createProjection(int& width, int& height)
{
	// Create and send projection matrix
	// FIXME: Needs to be decomposed and generalized for other shapes and shaders
	glm::mat4 proj;
	proj = glm::ortho(0.0f, float(width), 0.0f, float(height), 0.1f, 1000.0f);
	glUniformMatrix4fv(squareLocs.proj, 1, GL_FALSE, glm::value_ptr(proj));
	// Create and send view matrix
	// FIXME: Needs to be decomposed and generalized, and also given to user for use
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	glUniformMatrix4fv(squareLocs.view, 1, GL_FALSE, glm::value_ptr(view));
}


void Renderer::square(float xCoord, float yCoord, float sLength, float r, float g, float b)
{
	// Push square into render buffer
	squareBuffer.push_back({ glm::vec3(xCoord, yCoord, 0.0f), sLength, r, g, b});
}


void Renderer::endFrame()
{
	// Set background color
	// FIXME: Give to user
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	renderSquares();

	glfwSwapBuffers(window);
	glfwPollEvents();
}


void Renderer::renderSquares()
{
	
	glBindVertexArray(squareVAO);

	for (squareObj& obj : squareBuffer)
	{
		prepObjRender(obj);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	squareBuffer.clear();
	glBindVertexArray(0);
}


void Renderer::prepObjRender(squareObj& obj)
{
	// Set and send correct scale and position of square
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, obj.xyz);
	model = glm::scale(model, glm::vec3(obj.sLength, obj.sLength, 1.0f));
	glUniformMatrix4fv(squareLocs.model, 1, GL_FALSE, glm::value_ptr(model));
	
	// Send color of square
	glUniform3f(squareLocs.color, obj.r, obj.g, obj.b);
}