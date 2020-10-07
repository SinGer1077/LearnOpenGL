#include "StandartFunctions.h"
#define GLEW_STATIC

#include <glew.h>
#include <glfw3.h>

#include <iostream>
#include <chrono>
#include <cmath>
#include <string>




/// <summary>
/// �������� ���� ��� ������� ESC
/// </summary>
/// <param name="window"></param>
/// <param name="key"></param>
/// <param name="scancode"></param>
/// <param name="action"></param>
/// <param name="mode"></param>
void key_callback_escape(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
/// <summary>
/// ���������� ���������� �������
/// </summary>
/// <param name="vertexShaderSource"></param>
void CompileVertexShader(GLuint* vertexShader, const GLchar* vertexShaderSource) {
	*vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(*vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(*vertexShader);
}
/// <summary>
/// ���������� ������������ �������
/// </summary>
/// <param name="fragmentShader"></param>
/// <param name="fragmentShaderSource"></param>
void CompileFragmentShader(GLuint* fragmentShader, const GLchar* fragmentShaderSource) {
	*fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(*fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(*fragmentShader);
}
/// <summary>
/// �������� �������� ���������� �������
/// </summary>
/// <param name="shader"></param>
/// <param name="shaderType"></param>
void CheckSuccessfulShaderCompilation(GLuint* shader, std::string shaderType) {
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(*shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::"<<shaderType<<"::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}
/// <summary>
/// ���������� ��������� ���������
/// </summary>
/// <param name="shaderProgram"></param>
/// <param name="vertexShader"></param>
/// <param name="fragmentShader"></param>
void CompileShaderProgram(GLuint* shaderProgram, GLuint* vertexShader, GLuint* fragmentShader) {
	*shaderProgram = glCreateProgram();
	glAttachShader(*shaderProgram, *vertexShader);
	glAttachShader(*shaderProgram, *fragmentShader);
	glLinkProgram(*shaderProgram);
	glDeleteShader(*fragmentShader);
	glDeleteShader(*vertexShader);
}
/// <summary>
/// ��������� ���������� ��������� ���������
/// </summary>
/// <param name="shaderProgram"></param>
void CheckSuccessfulProgramCompilation(GLuint* shaderProgram) {
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(*shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << "PROGRAM" << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}
/// <summary>
/// ��������� ������
/// </summary>
/// <param name="verticesFirst"></param>
/// <param name="size_vertices"></param>
/// <param name="VAO"></param>
/// <param name="VBO"></param>
void GenerationFigure(GLfloat verticesFirst[], int size_vertices, GLuint VAO, GLuint VBO) {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size_vertices, verticesFirst, GL_STATIC_DRAW);
	//std::cout << size_vertices << " " << verticesFirst;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void GenerationEBOFigure(GLfloat verticesFirst[], int size_vertices,GLuint indices[], int size_indices, GLuint VAO, GLuint VBO, GLuint EBO) {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size_vertices, verticesFirst, GL_STATIC_DRAW);
	std::cout << size_vertices << " " << verticesFirst << std::endl;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_indices, indices, GL_STATIC_DRAW);
	std::cout << size_indices << " " << indices;
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void GenerationTextureEBOFigure(GLfloat verticesFirst[], int size_vertices, GLuint indices[], int size_indices, GLuint VAO, GLuint VBO, GLuint EBO) {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size_vertices, verticesFirst, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_indices, indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));	
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

}
void UpdateFigure(GLfloat verticesFirst[], int size_vertices, GLuint VAO, GLuint VBO) {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size_vertices, verticesFirst, GL_STATIC_DRAW);
	//std::cout << size_vertices << " " << verticesFirst;
	//������� � ������������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//������� � ������
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}