#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h"
#include <iostream>

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "lib/glew32.lib")
#pragma comment(lib, "lib/glfw3.lib")

void InitApp()
{
	glClearColor(0, 0, 0, 0);
}

void ErrorCallback(int error, const char* description)
{
	std::cout << description << std::endl;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void WindowSizeChangeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main()
{
	// GLFW window handler
	// error handler
	GLFWwindow* window = NULL;
	glfwSetErrorCallback(ErrorCallback);

	// init GLFW 
	if (!glfwInit())
		exit(EXIT_FAILURE);

	// create window
	window = glfwCreateWindow(800, 600, "test", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// create context
	glfwMakeContextCurrent(window);

	// swap
	glfwSwapInterval(1);
	// key handler
	glfwSetKeyCallback(window, KeyCallback);
	// window size change handler
	glfwSetWindowSizeCallback(window, WindowSizeChangeCallback);
	// init GLFW
	glewInit();
	// init Application
	InitApp();

	// major rendering roop(repeat untill terminate window)
	while (!glfwWindowShouldClose(window)) {
		// remove buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// input update and render code
		// ...

		// change render buffer(display result of painting)
		glfwSwapBuffers(window);

		// window event polling
		glfwPollEvents();
	}

	// remove window
	glfwDestroyWindow(window);
	// exit GLFW
	glfwTerminate();
}