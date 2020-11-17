#pragma once

#include "GL.h"
#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h"
#include <iostream>

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "lib/glew32.lib")
#pragma comment(lib, "lib/glfw3.lib")

class Triangle {
private:
	int framebufferWidth, framebufferHeight;
	GLuint triangleVertexArrayObject;
	GLuint triangleShaderProgramID;
	GLuint trianglePositionVertexBufferObjectID;
	GLuint triangleColorVertexBufferObjectID;
public:
	bool InitShader();
	bool defineVertexArrayObject();
	void frameBufferSizeCallback(GLFWwindow*, int, int);
	void userProgramAndBind();
	void terminate();
};

