#pragma once
#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h"
#include <string>
#include <map>

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "lib/glew32.lib")
#pragma comment(lib, "lib/glfw3.lib")

class GL {
private:
	int width;
	int height;
	std::map<int, bool>key_status;
	GLFWwindow* window{ nullptr };
public:
	GL(const std::string&, const int, const int, const bool, const int display_ix = 0);
	~GL();

	GL& Init(const std::string&, const int, const int, const bool, const int display_ix = 0);
	void reportErrorAndExit(const std::string&, const std::string&);
	bool isKeyPressed(const int& key);
	bool isKeyReleased(const int& key);
	bool isKeyPressedAndReleased(const int& key);
	void handleKeyPress();
	void preDraw();
	void run();
};

