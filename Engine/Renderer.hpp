#ifndef RENDERER
#define RENDERER

#include <ShaderClass.h>
#include <vector>
// Matricies headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct GLFWwindow;


class Renderer
{
private:
	GLFWwindow* window;
	
	glm::mat4 proj;

	float squareVertices[12] =
	{
		0.0f, 0.0f, 1.0f, // Bottom Left (will scale/rotate from this point, as is at origin)
		0.0f, 1.0f, 1.0f, // Top Left 
		1.0f, 0.0f, 1.0f, // Bottom Right
		1.0f, 1.0f, 1.0f  // Top Right
	};


	int squareIndices[6] =
	{
		0, 1, 2, // First Triangle
		3, 2, 1 // Second Triangle
	};

	struct squareObj
	{
		glm::vec3 xyz;
		float sLength;
		float r, g, b;
	};

	struct locs
	{
		unsigned int proj, view, model, color;
	};

	locs squareLocs;
	Shader squareShader;
	std::vector<squareObj> squareBuffer;
	unsigned int squareVBO, squareVAO, squareEBO;

	void getLocs();
	void createProjection(int& width, int& height);
	void squareInit();

public:
	Renderer(int width, int height, GLFWwindow* win);

	void circle();
	void square(float xCoord, float yCoord, float sLength, float r, float g, float b);
	void endFrame();
	void renderSquares();
	void prepObjRender(squareObj& squareObj);
};

#endif