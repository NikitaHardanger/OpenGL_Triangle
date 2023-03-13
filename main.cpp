#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"



/*// Vertices coordinates TRIANGLE
GLfloat vertices[] =
{    //    COORDINATES                      //    COLORS             ||
	-0.5f, -0.5f * float(sqrt(3)) / 3,		0.0f,	0.8f, 0.3f,  0.02f,	// LEFT vertice
	 0.5f, -0.5f * float(sqrt(3)) / 3,		0.0f,	0.8f, 0.3f,  0.02f,	// RIGHT vertice
	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3 , 0.0f,	1.0f, 0.6f,  0.32f,	// UPPER vertice

	-0.25f, 0.5f * float(sqrt(3)) / 6,		0.0f,	0.9f, 0.45f, 0.17f,	// Inner left
	 0.25f, 0.5f * float(sqrt(3)) / 6,		0.0f,	0.9f, 0.45f, 0.17f,	// Inner right
	 0.0f, -0.5f * float(sqrt(3)) / 3,		0.0f,	0.8f, 0.3f,  0.02f	// Inner down
};


GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
};*/

// Vertices coordinates SQUARE
GLfloat vertices[] =
{    //    COORDINATES      //    COLORS             ||
	-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f,  0.0f, // LEFT vertice
	-0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	0.0f,  1.0f, // RIGHT vertice
	 0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	1.0f,  1.0f, // UPPER vertice
	 0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,	1.0f,  0.0f, // UPPER vertice

	-0.25f, 0.5f * float(sqrt(3)) / 6,		0.0f,	0.9f, 0.45f, 0.17f,	// Inner left
	 0.25f, 0.5f * float(sqrt(3)) / 6,		0.0f,	0.9f, 0.45f, 0.17f,	// Inner right
	 0.0f, -0.5f * float(sqrt(3)) / 3,		0.0f,	0.8f, 0.3f,  0.02f	// Inner down
};

GLuint indices[] =
{
	0, 2, 1,	// Upper triangle
	0, 3, 2		// Lower triangle
};

int main() 
{
	// Initializa GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using (3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Tell GLFW we are using the CORE profile
	// so that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWindow object of 800 by 800 pixels, naming it "OpenGL"
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);

	// ERROR check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Introduce the window into the current context
	glfwMakeContextCurrent(window);


	// Load GLAD so it configures OpenGL
	gladLoadGL();

	// Specify the viewport of OpenGL in the Window
	// x = 0, y = 0, -> x = 800, y = 800
	glViewport(0, 0, 800, 800);


	// Creates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Generates Vertex Array Object and blinds it
	VAO VAO1;
	VAO1.Bind();

	// Generate Vertex Buffer Object links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generate Element Buffer Object links it to vertices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such a coordinates and colors to VAO
	VAO1.linkAttribute(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.linkAttribute(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.linkAttribute(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");


	// Texture

	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load("cat.png", &widthImg, &heightImg, &numColCh, 0);

	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint texture0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");
	shaderProgram._Activate();
	glUniform1i(texture0Uni, 0);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Set Color for background
		glClearColor(0.235f, 0.173f, 0.388f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram._Activate();
		// Assigns a value to the uniform;
		glUniform1f(uniID, 0.5f);
		glBindTexture(GL_TEXTURE_2D, texture);
		VAO1.Bind();
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		// GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we`ve created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	glDeleteTextures(1, &texture);
	shaderProgram._Delete();

	// Delete window before ending program
	glfwDestroyWindow(window);

	// Terminate GLFW before ending program
	glfwTerminate();
	return 0;
}