#define GLEW_STATIC

#include <glew.h>
#include <glfw3.h>

#include <iostream>
#include <chrono>
#include <cmath>
#include <string>

#include "Shaders.h"
#include "StandartFunctions.h"

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow* window = glfwCreateWindow(800, 800, "Uniform Triangle", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to init glew" << std::endl;
		return -1;
	}
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glfwSetKeyCallback(window, key_callback_escape);

	Shaders shaders;
	GLuint vertexShader;
	CompileVertexShader(&vertexShader, shaders.gradientVertexShader);
	CheckSuccessfulShaderCompilation(&vertexShader, "vertexShader");

	GLuint fragmentShader;
	CompileFragmentShader(&fragmentShader, shaders.gradientFragmentShader);
	CheckSuccessfulShaderCompilation(&fragmentShader, "fragmentShader");

	GLuint shaderProgram;
	CompileShaderProgram(&shaderProgram, &vertexShader, &fragmentShader);
	CheckSuccessfulProgramCompilation(&shaderProgram);

	GLfloat verticesFirst[] = {
		// �������             //�����
		0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, //������� ����
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, //������ ������ ����
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f //������ ����� ����
	};


	GLuint VBO;
	GLuint VAO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	UpdateFigure(verticesFirst, sizeof(verticesFirst), VAO, VBO);

	while (!glfwWindowShouldClose(window)) {

		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		GLfloat timeValue = glfwGetTime(); // �������� ������� �����
		GLfloat greenValue = (sin(timeValue) / 2) + 0.1; //��� ����� ������ ������� ���� � ����������� �� �������
		GLfloat redValue = (sin(timeValue) / 2) + 0.1;
		GLfloat blueValue = (sin(timeValue) / 2) + 0.1;
		GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "flexColor"); //���� �������� (?)
		glUseProgram(shaderProgram);
		glUniform3f(vertexColorLocation, redValue, greenValue, blueValue);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glfwTerminate();

	return 0;
};
