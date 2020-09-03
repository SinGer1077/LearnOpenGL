#define GLEW_STATIC // ���������� glew ��� ����������� ���������� 
#include <glew.h> // ���������� glew
#include <glfw3.h> // ���������� glfw
#include <iostream>

// ��������� ������ �� ����� GLSL
const GLchar* vertexShaderSource = "#version 330 core\n" // �������� ������ ������� + profie
"layout (location=0) in vec3 position;\n" //�������� ������� ������ � ������� in (vec3), ������� ���������� ����� layout
"void main()\n"
"{\n"
	"gl_Position = vec4(position.x, position.y, position.z, 1.0f);\n" // ��������� ������ �������, ����� ������������� vec3 � vec4
"}\0";

// ����������� ������
const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n" // �������� �������� ������ (���� ������� RGBA)
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n" // ������� �����
"}\0";

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{ // ��������� �� ����, ������� �������, �������� ��� ��������, ����� ����������� ������������ (shift, control, alt, super)
	// ����� ������������ �������� ESC, �� ������������� �������� windowShouldClose � true,
	//  � ���������� ���������
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
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
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
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
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//�������� ���������� ������ �������	
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success); // �������� ����������
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog); // ���� ����� ������, �� �� �������
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION FAILED\n" << infoLog << std::endl;
	}


	//������� ������� ����, ������������ ���� �� �������� GLFW ������������
	while (!glfwWindowShouldClose(window)) //�������� �� ���������� � ��������
	{
		glfwPollEvents(); // ���� �� ������� �����-���� �������

		// ������� ��������� �����
		glClearColor(0.2f, 0.3f, 0.3f, 1.0); // ������������� ����, ������� ������ �����
		glClear(GL_COLOR_BUFFER_BIT); //glClear - ������� �����. ��������� ���, ����� ������� ����� ����� ����� ��������
		
		//������������ 3 3� ������� ��� ��������� ������������
		GLfloat vertices[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};
		GLuint VBO; // ������ ���������� ������ ��� �������� ������ � GPU
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO); // �������� ���� ������
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // ����������� ��������� ������ � �����
		//1. ��� ������, �� ������� ��������� ������, 2. ������ ������ � ������. 3. ���� ������, 4.������ ������ ������ � �������
		// GL_STATIC_DRAW - ������ ���� ������� �� ��������, ���� �������� �����
		// GL_DYNAMIC_DRAW - ������ �������� �����
		// GL_STREAM_DRAW - ������ �������� ��� ������ ���������

		glfwSwapBuffers(window); // ������ ��������� ������ � ������������ � ���������
		
	}

	




	// ����� �� �������� �����, ����� �������� ������
	glfwTerminate();
	return 0;
	
}

