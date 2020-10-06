#define GLEW_STATIC

#include <glew.h>
#include <glfw3.h>

#include <iostream>
#include <chrono>
#include <cmath>
#include <string>

#include "Shaders.h"

/// <summary>
/// Закрытие окна при нажатии ESC
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
/// Компиляция вершинного шейдера
/// </summary>
/// <param name="vertexShaderSource"></param>
void CompileVertexShader(GLuint *vertexShader, const GLchar *vertexShaderSource) {	
	*vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(*vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(*vertexShader);
}
/// <summary>
/// Компиляция фрагментного шейдера
/// </summary>
/// <param name="fragmentShader"></param>
/// <param name="fragmentShaderSource"></param>
void CompileFragmentShader(GLuint *fragmentShader, const GLchar* fragmentShaderSource) {
	*fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(*fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(*fragmentShader);
}
/// <summary>
/// Проверка успешной компиляции шейдера
/// </summary>
/// <param name="shader"></param>
/// <param name="shaderType"></param>
void CheckSuccessfulShaderCompilation(GLuint *shader, std::string shaderType) {
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(*shader, 512, NULL, infoLog);
		std::cout << "Failed " <<shaderType<< " compiling" << std::endl;
	}
}
/// <summary>
/// Компиляция шейдерной программы
/// </summary>
/// <param name="shaderProgram"></param>
/// <param name="vertexShader"></param>
/// <param name="fragmentShader"></param>
void CompileShaderProgram(GLuint *shaderProgram, GLuint *vertexShader, GLuint *fragmentShader) {
	*shaderProgram = glCreateProgram();
	glAttachShader(*shaderProgram, *vertexShader);
	glAttachShader(*shaderProgram, *fragmentShader);
	glLinkProgram(*shaderProgram);
	glDeleteShader(*fragmentShader);
	glDeleteShader(*vertexShader);
}
/// <summary>
/// Проверяем компиляцию шейдерной программы
/// </summary>
/// <param name="shaderProgram"></param>
void CheckSuccessfulProgramCompilation(GLuint *shaderProgram) {
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(*shaderProgram, 512, NULL, infoLog);
		std::cout << "Failed to link program" << std::endl;
	}
}
void GenerationFigure(GLfloat verticesFirst[], int size_vertices,GLuint VAO, GLuint VBO) {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size_vertices, verticesFirst, GL_STATIC_DRAW);
	//std::cout << size_vertices << " " << verticesFirst;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
}


int main() {
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow* window = glfwCreateWindow(800, 800, "Two Triangles", nullptr, nullptr);
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
	CompileVertexShader(&vertexShader, shaders.vertexShaderSource);	
	CheckSuccessfulShaderCompilation(&vertexShader, "vertexShader");	

	GLuint fragmentShader;	
	CompileFragmentShader(&fragmentShader, shaders.fragmentShaderSource);
	CheckSuccessfulShaderCompilation(&fragmentShader, "fragmentShader");
	
	GLuint shaderProgram;
	CompileShaderProgram(&shaderProgram, &vertexShader, &fragmentShader);
	CheckSuccessfulProgramCompilation(&shaderProgram);

	GLfloat verticesFirst[] = {
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f		
	};
	

	GLuint VBO;
	GLuint VAO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);	

	GenerationFigure(verticesFirst, sizeof(verticesFirst),VAO, VBO);
		
	while (!glfwWindowShouldClose(window)) {
		
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);		
		glDrawArrays(GL_TRIANGLES, 0, 3);		
				
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glfwTerminate();

	return 0;
}