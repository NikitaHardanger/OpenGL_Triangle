#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

class VBO
{
public:
	// ID reference for te Vertex Buffer Object
	GLuint ID;
	// Constructor that gemerates a VBO ID
	VBO(GLfloat* vertices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};

#endif // !VBO_CLASS_H
