#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VBO.h"

class VAO
{
public:
	// ID reference for te Vertex Array Object
	GLuint ID;
	// Constructor that gemerates a VAO ID
	VAO();

	// LINKS a VBO to the VAO using a certain layout
	void linkAttribute(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	// Bind the VAO
	void Bind();
	// Unbind the VAO
	void Unbind();
	// Deletes the VAO
	void Delete();
};

#endif // !VAO_CLASS_H
