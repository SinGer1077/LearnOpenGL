#define GLEW_STATIC

#include <glew.h>
#include <glfw3.h>

#include <iostream>
#include <chrono>
#include <cmath>
#include <string>




	/// <summary>
/// Закрытие окна при нажатии ESC
/// </summary>
/// <param name="window"></param>
/// <param name="key"></param>
/// <param name="scancode"></param>
/// <param name="action"></param>
/// <param name="mode"></param>
void key_callback_escape(GLFWwindow* window, int key, int scancode, int action, int mode);
	/// <summary>
	/// Компиляция вершинного шейдера
	/// </summary>
	/// <param name="vertexShaderSource"></param>
void CompileVertexShader(GLuint* vertexShader, const GLchar* vertexShaderSource);
	/// <summary>
	/// Компиляция фрагментного шейдера
	/// </summary>
	/// <param name="fragmentShader"></param>
	/// <param name="fragmentShaderSource"></param>
void CompileFragmentShader(GLuint* fragmentShader, const GLchar* fragmentShaderSource);
	/// <summary>
	/// Проверка успешной компиляции шейдера
	/// </summary>
	/// <param name="shader"></param>
	/// <param name="shaderType"></param>
void CheckSuccessfulShaderCompilation(GLuint* shader, std::string shaderType);
	/// <summary>
	/// Компиляция шейдерной программы
	/// </summary>
	/// <param name="shaderProgram"></param>
	/// <param name="vertexShader"></param>
	/// <param name="fragmentShader"></param>
void CompileShaderProgram(GLuint* shaderProgram, GLuint* vertexShader, GLuint* fragmentShader);
	/// <summary>
	/// Проверяем компиляцию шейдерной программы
	/// </summary>
	/// <param name="shaderProgram"></param>
void CheckSuccessfulProgramCompilation(GLuint* shaderProgram);
	/// <summary>
	/// Генерация буфера
	/// </summary>
	/// <param name="verticesFirst"></param>
	/// <param name="size_vertices"></param>
	/// <param name="VAO"></param>
	/// <param name="VBO"></param>
void GenerationFigure(GLfloat verticesFirst[], int size_vertices, GLuint VAO, GLuint VBO);

