#include "GL.h"
#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h"
#include "Shader.h"
#include <string>
#include <iostream>

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "lib/glew32.lib")
#pragma comment(lib, "lib/glfw3.lib")

GL::GL(const std::string& title, const int width, const int height, const bool use_full_screen, const int display_ix) {
	Init(title, width, height, use_full_screen, display_ix);
}

GL::~GL() {
	glfwDestroyWindow(window);
}

GL& GL::Init(const std::string& title, const int _width, const int _height, const bool use_full_screen, const int display_ix) {
	if (window != nullptr) {
		std::cout << "Skip second initialization" << std::endl;
		return *this;
	}

	if (!glfwInit()) {
		reportErrorAndExit(__FUNCTION__, "glfw initialization");
	}

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	int num_monitors;
	GLFWmonitor** monitors = glfwGetMonitors(&num_monitors);

	if (!use_full_screen) {
		window = glfwCreateWindow(_width, _height, title.c_str(), NULL, NULL);

		// center window
		int display_w, display_h;
		glfwMakeContextCurrent(window);
		glfwGetFramebufferSize(window, &display_w, &display_h);

		width = display_w;
		height = display_h;

		glfwSetWindowPos(window, (mode->width - display_w) / 2, (mode->height - display_h) / 2);
	}
	else {
		if (display_ix < num_monitors) { 
			// display_ix is valid
			window = glfwCreateWindow(mode->width, mode->height, title.c_str(), monitors[display_ix], NULL);
		}
		else {
			window = glfwCreateWindow(mode->width, mode->height, title.c_str(), glfwGetPrimaryMonitor(), NULL);
		}

		// full screen resolution
		width = mode->width;
		height = mode->height;
	}

	if (!window) {
		reportErrorAndExit(__FUNCTION__, "Window initialization");
	}

	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		reportErrorAndExit(__FUNCTION__, "glew initialization");
	}

	const float aspect_ratio = (float)width / (float)height;
	glViewport(0, 0, width, height);
	glOrtho(-aspect_ratio, aspect_ratio, -1.0, 1.0, -1.0, 1.0);
	std::cout << "Display width = " << width << " height = " << height <<
		" Aspect ratio is " << aspect_ratio << std::endl;

	// anti-aliasing
	glfwWindowHint(GLFW_SAMPLES, 32);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return *this;
}

void GL::reportErrorAndExit(const std::string& function_name, const std::string& message)
{
	std::cout << "Error: " << function_name << " " << message << std::endl;

	glfwTerminate();
	getchar(); // pause to read error message
	exit(1);
}

bool GL::isKeyPressed(const int& key)
{
	if (key_status.count(key) <= 0) {
		key_status[key] = false;
	}

	if (glfwGetKey(window, key) == GLFW_PRESS) {
		key_status[key] = true;
	}
	else {
		key_status[key] = false;
	}

	return key_status[key];
}

bool GL::isKeyReleased(const int& key) {
	if (key_status.count(key) <= 0) {
		key_status[key] = false;
	}

	if (glfwGetKey(window, key) == GLFW_RELEASE) {
		key_status[key] = false;
	}
	else {
		key_status[key] = true;
	}

	return key_status[key];
}

bool GL::isKeyPressedAndReleased(const int& key) {
	if (key_status.count(key) <= 0) { 
		key_status[key] = false;
	}

	if (glfwGetKey(window, key) == GLFW_RELEASE) {
		if (key_status[key] == true) {
			key_status[key] = false;
			return true;
		}
		else {
			key_status[key] = false;
			return false;
		}
	}
	else {
		key_status[key] = true;
		return false;
	}
	
}

void GL::preDraw() {
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1);			 // while background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
}

void GL::handleKeyPress() {
	// add key event
	if (isKeyPressed(GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(window, true);
	}
}

void GL::run() {
	if (window == nullptr) {
		Init("Canvas", 1280, 960, false);
	}

	float position[] = {
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};

	float color[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f
	};

	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
	};

	Shader object;
	if (!object.InitShaderProgram()) {
		std::cerr << "Error: Shader积己 角菩" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	size_t v_size = sizeof(position) / sizeof(float);
	size_t e_size = sizeof(elements) / sizeof(GLuint);

	if (!object.defineVertexObject(position, color, v_size, elements, e_size)) {
		std::cerr << "Error: Shader积己 角菩" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	object.useProgramAndBind();

	// main loop 
	while (!glfwWindowShouldClose(window)) {
		handleKeyPress();
		
		preDraw();

		//update();	// the major worker function
		object.drawObject();

		glPopMatrix();

		// post draw
		glfwSwapBuffers(window); // double buffering
		glfwPollEvents();
	}
	object.TerminateProgram();

	glfwTerminate();
}