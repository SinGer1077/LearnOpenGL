#define GLEW_STATIC

#include <glew.h>
#include <glfw3.h>
#include <SOIL.h>

#include <iostream>
#include <chrono>
#include <cmath>
#include <string>

#include "Shaders.h"
#include "StandartFunctions.h"


int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow* window = glfwCreateWindow(800, 800, "One Triangle", nullptr, nullptr);
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
	CompileVertexShader(&vertexShader, shaders.textureVertexShader);
	CheckSuccessfulShaderCompilation(&vertexShader, "vertexShader");

	GLuint fragmentShader;
	CompileFragmentShader(&fragmentShader, shaders.textureFragmentShader);
	CheckSuccessfulShaderCompilation(&fragmentShader, "fragmentShader");

	GLuint shaderProgram;
	CompileShaderProgram(&shaderProgram, &vertexShader, &fragmentShader);
	CheckSuccessfulProgramCompilation(&shaderProgram);

	GLfloat vertices[] = {
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, //� �
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, //� �
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, //� �
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f //� �
	};
	GLuint indices[] = { // ������� �����
		0,1,3, // ������ �����������
		1,2,3 // ������ �����������
	};	

	GLuint VBO;
	GLuint VAO;
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	GenerationTextureEBOFigure(vertices, sizeof(vertices), indices, sizeof(indices), VAO, VBO, EBO);

	int texWidth, texHeight;
	unsigned char* image = SOIL_load_image("Textures//container.jpg", &texWidth, &texHeight, 0, SOIL_LOAD_RGB); //�������� ������ �����������
	//�������������� //������� � ������� ��������� ����������� //���-�� ������� ����������� //����� ���� RGB ���� �������.
	//��������� � ������� ������� ����
	GLuint texture1;
	glGenTextures(1, &texture1); //��������� �������������� ��������
	glBindTexture(GL_TEXTURE_2D, texture1); //�������� ��������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image); //��������� ��������
	glGenerateMipmap(GL_TEXTURE_2D);
	//1 - ����, 2� �����������
	//2 - ������� ������� ��� ��������� ��������, 0 - ��������� �� ogl
	//3 - � ����� ������� ������ ����������� - ������ ��� ��������
	//45 - ������ ������ �������������� ��������
	//6 - ������ 0 (�������� �������)?
	//7 - ������ ��������� �����������
	//8 - ��� ������ �����������
	//9 - ���� �����������
	SOIL_free_image_data(image); //����������� ������ �� �����������
	glBindTexture(GL_TEXTURE_2D, 0); //���������� ������ ��������

	image = SOIL_load_image("Textures//milos.jpg", &texWidth, &texHeight, 0, SOIL_LOAD_RGB); //�������� ������ �����������
	//�������������� //������� � ������� ��������� ����������� //���-�� ������� ����������� //����� ���� RGB ���� �������.
	//��������� � ������� ������� ����
	GLuint texture2;
	glGenTextures(1, &texture2); //��������� �������������� ��������
	glBindTexture(GL_TEXTURE_2D, texture2); //�������� ��������
	float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image); //��������� ��������
	glGenerateMipmap(GL_TEXTURE_2D);
	//1 - ����, 2� �����������
	//2 - ������� ������� ��� ��������� ��������, 0 - ��������� �� ogl
	//3 - � ����� ������� ������ ����������� - ������ ��� ��������
	//45 - ������ ������ �������������� ��������
	//6 - ������ 0 (�������� �������)?
	//7 - ������ ��������� �����������
	//8 - ��� ������ �����������
	//9 - ���� �����������
	SOIL_free_image_data(image); //����������� ������ �� �����������
	glBindTexture(GL_TEXTURE_2D, 0); //���������� ������ ��������

	while (!glfwWindowShouldClose(window)) {

		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture1"), 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture2"), 1);
		 
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);	
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
	glfwTerminate();

	return 0;
}