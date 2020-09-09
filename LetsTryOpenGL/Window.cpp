#define GLEW_STATIC // ���������� glew ��� ����������� ���������� 
#include <glew.h> // ���������� glew
#include <glfw3.h> // ���������� glfw
#include <iostream>

// ��������� ������ �� ����� GLSL
const GLchar* vertexShaderSource1 = "#version 330 core\n" // �������� ������ ������� + profie
"layout (location=0) in vec3 position;\n" //�������� ������� ������ � ������� in (vec3), ������� ���������� ����� layout
"void main()\n"
"{\n"
	"gl_Position = vec4(position.x, position.y, position.z, 1.0f);\n" // ��������� ������ �������, ����� ������������� vec3 � vec4
"}\0";

// ����������� ������
const GLchar* fragmentShaderSource1 = "#version 330 core\n"
"out vec4 color;\n" // �������� �������� ������ (���� ������� RGBA)
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.0f, 0.3f, 1.0f);\n" // ������� �����
"}\0";

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{ // ��������� �� ����, ������� �������, �������� ��� ��������, ����� ����������� ������������ (shift, control, alt, super)
	// ����� ������������ �������� ESC, �� ������������� �������� windowShouldClose � true,
	//  � ���������� ���������
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main_first()
{
	//������������� GLFW
	glfwInit();
	// ���������� GLFW
	// �������� ����������� ��������� ������ opengl
	// ��������
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// ��������
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// ��������� �������� ��� �������� ��������� ��������
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// ���������� ����������� ��������� ������� ����
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// ������� ������ ����
	GLFWwindow* window = glfwCreateWindow(800, 800, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//������������� GLEW 
	glewExperimental = GL_TRUE; //������������� �������� ������ ��� ���������� ������������ opengl, ��� ��� ����� ���� �������� � core-profile
	if (glewInit() != GLEW_OK) 
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// ������������� ������� ��������������� ����
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glfwSetKeyCallback(window, key_callback); // ����� �������� �� ESC

	//������ ������� ������
	GLuint vertexShader; // ������ � �������� - ����� �������������, ������� uint
	vertexShader = glCreateShader(GL_VERTEX_SHADER); // ��� ������������ �������
	// ����������� �������� ��� ������� � ���������� ������� � �����������
	glShaderSource(vertexShader, 1, &vertexShaderSource1, NULL);
	glCompileShader(vertexShader);
	//�������� ���������� ������ �������
	GLint success; // ����� ��� ����������� ���������� ������
	GLchar infoLog[512]; // ��������� ��� �������� ������ (���� ���������)
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); // �������� ����������
	if (!success) 
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog); // ���� ����� ������, �� �� �������
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION FAILED\n" << infoLog << std::endl;
	}

	// ������ ������������ �������
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // ��� ������������ �������
	glShaderSource(fragmentShader, 1, &fragmentShaderSource1, NULL);
	glCompileShader(fragmentShader);
	//�������� ���������� ������ �������	
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success); // �������� ����������
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog); // ���� ����� ������, �� �� �������
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION FAILED\n" << infoLog << std::endl;
	}

	// �������� ��������� ���������
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader); // ������������ � ��������� ��������� ������
	glAttachShader(shaderProgram, fragmentShader); // ������������ � ��������� ����������� ������
	glLinkProgram(shaderProgram); // ��������� �������
	// �������� ���������� ����������
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::LINK::LINKED FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader); // ������� �������, ��� ��� ������ �� ����� ����� ����������
	glDeleteShader(fragmentShader);

	//������������ 3 3� ������� ��� ��������� ������������
	//GLfloat vertices[] = {
	//	-0.5f, -0.5f, 0.0f,
	//	0.5f, -0.5f, 0.0f,
	//	0.0f, 0.5f, 0.0f
	//};
	GLfloat vertices[] = { // ���� ��������������
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};
	GLuint VBO; // ������ ���������� ������ ��� �������� ������ � GPU
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // �������� ���� ������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // ����������� ��������� ������ � �����
	//1. ��� ������, �� ������� ��������� ������, 2. ������ ������ � ������. 3. ���� ������, 4.������ ������ ������ � �������
	// GL_STATIC_DRAW - ������ ���� ������� �� ��������, ���� �������� �����
	// GL_DYNAMIC_DRAW - ������ �������� �����
	// GL_STREAM_DRAW - ������ �������� ��� ������ ���������

	GLuint VAO; // ������ ���������� �������
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO); // ������������� VAO

	// ���������� openlg, ��� ���������������� ��������� ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	// ������ ������� - ����� �������� ����� ��������� (� ����� ������ position, ������� ������� ����� layout (location=0)
	// ������ ��������� � ������� (��� vec3, ��������� 3)
	// ��� ������
	// ���������� ������������� ������� ������?
	// ���������� ����� �������� ������ 
	// �������� ������ ������ � ������ (� ��� �� �����)
	GLuint indices[] = { // ������� �����
		0,1,3, // ������ �����������
		1,2,3 // ������ �����������
	};
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0); // �������� �������
	glBindVertexArray(0); // ���������� VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	//���������� EBO, ������ �������������
	//GLfloat vertices[] = { // ���� ��������������
	//	0.5f, 0.5f, 0.0f,
	//	0.5f, -0.5f, 0.0f,
	//	-0.5f, -0.5f, 0.0f,
	//	-0.5f, 0.5f, 0.0f
	//};
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//������� ������� ����, ������������ ���� �� �������� GLFW ������������
	while (!glfwWindowShouldClose(window)) //�������� �� ���������� � ��������
	{
		glfwPollEvents(); // ���� �� ������� �����-���� �������

		// ������� ��������� �����
		glClearColor(0.2f, 0.3f, 0.3f, 1.0); // ������������� ����, ������� ������ �����
		glClear(GL_COLOR_BUFFER_BIT); //glClear - ������� �����. ��������� ���, ����� ������� ����� ����� ����� ��������
		
		glUseProgram(shaderProgram); // ������������� ���������
		
		glBindVertexArray(VAO); // ����� ����������� VAO
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0); // ���������� �� ���� �������������
			
		glfwSwapBuffers(window); // ������ ��������� ������ � ������������ � ���������
		
	}

	




	// ����� �� �������� �����, ����� �������� ������
	glfwTerminate();
	return 0;
	
}

