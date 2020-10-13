#define GLEW_STATIC

#include <glew.h>
#include <glfw3.h>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <chrono>
#include <cmath>
#include <string>

#include "Shaders.cpp"
#include "StandartFunctions.h"
void key_callback_regulate_texture(GLFWwindow* window, int key, int scancode, int action, int mode);
float mixCoef;

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

	Shader ourShader("Shaders//vertexTexture.txt", "Shaders//fragmentTexture.txt");
	/*GLuint vertexShader;
	CompileVertexShader(&vertexShader, shaders.textureVertexShader);
	CheckSuccessfulShaderCompilation(&vertexShader, "vertexShader");

	GLuint fragmentShader;
	CompileFragmentShader(&fragmentShader, shaders.textureFragmentShader);
	CheckSuccessfulShaderCompilation(&fragmentShader, "fragmentShader");

	GLuint shaderProgram;
	CompileShaderProgram(&shaderProgram, &vertexShader, &fragmentShader);
	CheckSuccessfulProgramCompilation(&shaderProgram);*/

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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
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

	image = SOIL_load_image("Textures//milos.jpg", &texWidth, &texHeight, 0, SOIL_LOAD_RGB); //�������� ������ �����������
	//�������������� //������� � ������� ��������� ����������� //���-�� ������� ����������� //����� ���� RGB ���� �������.
	//��������� � ������� ������� ����
	GLuint texture2;
	glGenTextures(1, &texture2); //��������� �������������� ��������
	glBindTexture(GL_TEXTURE_2D, texture2); //�������� ��������
	float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
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
	glfwSetKeyCallback(window, key_callback_regulate_texture);	
	
	while (!glfwWindowShouldClose(window)) {

		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ourShader.Use();
		//glUseProgram(shaderProgram);

		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::rotate(trans, glm::radians((GLfloat)glfwGetTime()*50.0f), glm::vec3(1.0, 1.0, 1.0));
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		GLuint transformLoc = glGetUniformLocation(ourShader.Program, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture2"), 1);		
		 
		glUniform1f(glGetUniformLocation(ourShader.Program, "mixCoef"), mixCoef);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);			
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glm::mat4 trans1 = glm::mat4(1.0f);
		trans1 = glm::scale(trans1, glm::vec3(sin((GLfloat)glfwGetTime()) / 2, sin((GLfloat)glfwGetTime()) / 2, 1.0f));
		trans1 = glm::translate(trans1, glm::vec3(0.5f, -0.5f, 0.0f));

		//trans1 = glm::scale(trans1, glm::vec3(sin((GLfloat)glfwGetTime())/2, sin((GLfloat)glfwGetTime())/2, 1.0f));
		//
		GLuint transformLoc1 = glGetUniformLocation(ourShader.Program, "transform");
		glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(trans1));		
		
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

void key_callback_regulate_texture(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		if (mixCoef < 1.0f)
			mixCoef += 0.1f;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		if (mixCoef > 0.0f)
			mixCoef -= 0.1f;
	}
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}