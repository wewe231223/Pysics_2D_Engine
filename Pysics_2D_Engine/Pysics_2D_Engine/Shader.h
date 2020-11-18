#pragma once

#include "GL.h"
#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h"
#include <iostream>

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "lib/glew32.lib")
#pragma comment(lib, "lib/glfw3.lib")

class Shader {
private:
	int framebufferWidth, framebufferHeight;
	GLuint triangleVertexArrayObject;
	GLuint triangleShaderProgramID;
	GLuint trianglePositionVertexBufferObjectID;
	GLuint triangleColorVertexBufferObjectID;
	size_t e_size;
public:
	bool InitShaderProgram();
	bool defineVertexObject(const float* position, const float* color, size_t f_size, const GLuint* elements, size_t e_size);
	void useProgramAndBind();
	void drawObject();
	void TerminateProgram();
};

