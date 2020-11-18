#include "Shader.h"

bool Shader::InitShaderProgram() {
	const GLchar* vertexShaderSource =
		"#version 330 core\n"
		"in vec3 positionAttribute;"
		"in vec3 colorAttribute;"
		"out vec3 passColorAttribute;"
		"void main()"
		"{"
		"gl_Position = vec4(positionAttribute, 1.0);"
		"passColorAttribute = colorAttribute;"
		"}";

	const GLchar* fragmentShaderSource =
		"#version 330 core\n"
		"in vec3 passColorAttribute;"
		"out vec4 fragmentColor;"
		"void main()"
		"{"
		"fragmentColor = vec4(passColorAttribute, 1.0);"
		"}";

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
		glDeleteShader(vertexShader);
		return false;
	}


	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << std::endl;
		return false;
	}

	triangleShaderProgramID = glCreateProgram();

	glAttachShader(triangleShaderProgramID, vertexShader);
	glAttachShader(triangleShaderProgramID, fragmentShader);

	glLinkProgram(triangleShaderProgramID);


	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	glGetProgramiv(triangleShaderProgramID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(triangleShaderProgramID, 512, NULL, errorLog);
		std::cerr << "ERROR: shader program 연결 실패\n" << errorLog << std::endl;
		return false;
	}

	return true;
}

bool Shader::defineVertexObject(const float* position, const float* color, size_t f_size, const GLuint* elements, size_t e_size) {
	size_t vertex_size = sizeof(float) * f_size;
	size_t elements_size = sizeof(GLuint) * e_size;
	this->e_size = e_size;

	glGenBuffers(1, &trianglePositionVertexBufferObjectID);
	glBindBuffer(GL_ARRAY_BUFFER, trianglePositionVertexBufferObjectID);
	glBufferData(GL_ARRAY_BUFFER, vertex_size, position, GL_STATIC_DRAW);

	glGenBuffers(1, &triangleColorVertexBufferObjectID);
	glBindBuffer(GL_ARRAY_BUFFER, triangleColorVertexBufferObjectID);
	glBufferData(GL_ARRAY_BUFFER, vertex_size, color, GL_STATIC_DRAW);

	glGenVertexArrays(1, &triangleVertexArrayObject);
	glBindVertexArray(triangleVertexArrayObject);

	GLuint triangleElementBufferObject;
	glGenBuffers(1, &triangleElementBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleElementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements_size, elements, GL_STATIC_DRAW);


	GLint positionAttribute = glGetAttribLocation(triangleShaderProgramID, "positionAttribute");

	if (positionAttribute == -1) {
		std::cerr << "position 속성 설정 실패" << std::endl;
		return false;
	}

	glBindBuffer(GL_ARRAY_BUFFER, trianglePositionVertexBufferObjectID);
	glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(positionAttribute);

	GLint colorAttribute = glGetAttribLocation(triangleShaderProgramID, "colorAttribute");

	if (colorAttribute == -1) {
		std::cerr << "color 속성 설정 실패" << std::endl;
		return false;
	}

	glBindBuffer(GL_ARRAY_BUFFER, triangleColorVertexBufferObjectID);
	glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colorAttribute);

	glBindVertexArray(0);

	return true;
}

void Shader::useProgramAndBind() {
	glUseProgram(triangleShaderProgramID);
	glBindVertexArray(triangleVertexArrayObject);
}

void Shader::drawObject() {
	glDrawElements(GL_TRIANGLES, e_size, GL_UNSIGNED_INT, 0);
}

void Shader::TerminateProgram() {
	glUseProgram(0);
	glBindVertexArray(0);
	glDeleteProgram(triangleShaderProgramID);
	glDeleteBuffers(1, &trianglePositionVertexBufferObjectID);
	glDeleteBuffers(1, &triangleColorVertexBufferObjectID);
	glDeleteVertexArrays(1, &triangleVertexArrayObject);
}
