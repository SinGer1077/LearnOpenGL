#define GLEW_STATIC // подключаем glew как статическую библиотеку 
#include <glew.h> // подключаем glew
#include <glfw3.h> // подключаем glfw
#include <iostream>

// вершинный шейдер на языке GLSL
const GLchar* vertexShaderSource1 = "#version 330 core\n" // указание версии шейдера + profie
"layout (location=0) in vec3 position;\n" //указание входных данных с помощью in (vec3), позиция переменной через layout
"void main()\n"
"{\n"
	"gl_Position = vec4(position.x, position.y, position.z, 1.0f);\n" // результат работы шейдера, нужно преобразовать vec3 в vec4
"}\0";

// фрагментный шейдер
const GLchar* fragmentShaderSource1 = "#version 330 core\n"
"out vec4 color;\n" // указание выходных данных (цвет формате RGBA)
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.0f, 0.3f, 1.0f);\n" // задание цвета
"}\0";

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{ // указатель на окно, нажатая клавиша, действие над клавишей, число описывающее модификаторы (shift, control, alt, super)
	// Когда пользователь нажимает ESC, мы устанавливаем свойство windowShouldClose в true,
	//  и приложение закроется
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main_first()
{
	//инициализация GLFW
	glfwInit();
	// найстройка GLFW
	// задается минимальная требуемая версия opengl
	// мажорная
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// минорная
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// установка профайла для которого создается контекст
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// выключение возможности изменения размера окна
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// создаем объект окна
	GLFWwindow* window = glfwCreateWindow(800, 800, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//инициализация GLEW 
	glewExperimental = GL_TRUE; //использование новейших техник для управления функционалом opengl, без нее могут быть проблемы с core-profile
	if (glewInit() != GLEW_OK) 
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// устанавливаем размеры отрисовываемого окна
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glfwSetKeyCallback(window, key_callback); // вызов закрытия на ESC

	//сборка шейдера вершин
	GLuint vertexShader; // доступ к объектам - через идентификатор, поэтому uint
	vertexShader = glCreateShader(GL_VERTEX_SHADER); // тип создаваемого шейдера
	// привязываем исходный код шейдера к созданному шейдеру и компилируем
	glShaderSource(vertexShader, 1, &vertexShaderSource1, NULL);
	glCompileShader(vertexShader);
	//проверка успешности сборки шейдера
	GLint success; // число для определения успешности сборки
	GLchar infoLog[512]; // контейнер для хранения ошибок (если появились)
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); // проверка успешности
	if (!success) 
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog); // если будет ошибка, мы ее выведем
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION FAILED\n" << infoLog << std::endl;
	}

	// сборка фрагментного шейдера
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // тип создаваемого шейдера
	glShaderSource(fragmentShader, 1, &fragmentShaderSource1, NULL);
	glCompileShader(fragmentShader);
	//проверка успешности сборки шейдера	
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success); // проверка успешности
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog); // если будет ошибка, мы ее выведем
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION FAILED\n" << infoLog << std::endl;
	}

	// создание шейдерной программы
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader); // присоединяем к программе вершинный шейдер
	glAttachShader(shaderProgram, fragmentShader); // присоденияем к программе фрагментный шейдер
	glLinkProgram(shaderProgram); // связываем шейдеры
	// проверка успешности связывания
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::LINK::LINKED FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader); // удаляем шейдеры, они нам больше не нужны после связывания
	glDeleteShader(fragmentShader);

	//представляем 3 3д вершины для отрисовки треугольника
	//GLfloat vertices[] = {
	//	-0.5f, -0.5f, 0.0f,
	//	0.5f, -0.5f, 0.0f,
	//	0.0f, 0.5f, 0.0f
	//};
	GLfloat vertices[] = { // углы прямоугольника
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};
	GLuint VBO; // объект вершинного буфера для отправки данных в GPU
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // привязка типа буфера
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // копирование вершинных данных в буфер
	//1. тип буфера, на который скидываем данные, 2. размер данных в байтах. 3. сами данные, 4.способ работы видюхи с данными
	// GL_STATIC_DRAW - данные либо никогда не меняются, либо меняются редко
	// GL_DYNAMIC_DRAW - данные меняются часто
	// GL_STREAM_DRAW - данные меняются при каждой отрисовке

	GLuint VAO; // объект вершинного массива
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO); // использование VAO

	// показываем openlg, как интерпретировать вершинные данные
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	// первая позиция - какой аргумент хотим настроить (в нашем случае position, которую указали через layout (location=0)
	// размер аргумента в шейдере (был vec3, указываем 3)
	// тип данных
	// необходимо нормализовать входные данные?
	// расстояние между наборами данных 
	// смещение начала данных в буфере (у нас не имеет)
	GLuint indices[] = { // индексы углов
		0,1,3, // первый треугольник
		1,2,3 // второй треугольник
	};
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0); // включаем атрибут
	glBindVertexArray(0); // отвязываем VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	//используем EBO, рисуем прямоугольник
	//GLfloat vertices[] = { // углы прямоугольника
	//	0.5f, 0.5f, 0.0f,
	//	0.5f, -0.5f, 0.0f,
	//	-0.5f, -0.5f, 0.0f,
	//	-0.5f, 0.5f, 0.0f
	//};
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//создаем игровой цикл, отрисовываем пока не прикажем GLFW остановиться
	while (!glfwWindowShouldClose(window)) //получили ли инструкцию к закрытию
	{
		glfwPollEvents(); // были ли вызваны какие-либо события

		// командф отрисовки здесь
		glClearColor(0.2f, 0.3f, 0.3f, 1.0); // устанавливаем цвет, которым очищен буфер
		glClear(GL_COLOR_BUFFER_BIT); //glClear - очищаем буфер. Указываем бит, чтобы указать какой буфер нужно очистить
		
		glUseProgram(shaderProgram); // использование программы
		
		glBindVertexArray(VAO); // снова привязываем VAO
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0); // отвязываем до след использования
			
		glfwSwapBuffers(window); // замена цветового буфера в соответствии с операцией
		
	}

	




	// вышли из игрового цикла, нужно очистить данные
	glfwTerminate();
	return 0;
	
}

