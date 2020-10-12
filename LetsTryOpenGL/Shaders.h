
#define GLEW_STATIC
#include <glew.h>
//#include <glfw3.h>

class Shaders
{
public:
	const GLchar* vertexShaderSource = "#version 330 core\n"
		"layout (location=0) in vec3 position;\n"
		"void main() {\n"
		"gl_Position = vec4(position.x, position.y, position.z, 1.0f);}\0";

	const GLchar* fragmentShaderSource = "#version 330 core\n"
		"out vec4 color;\n"
		"void main() {\n"
		"color = vec4(0.9f, 0.0f, 0.7f, 1.0f);}\n";

	const GLchar* fragmentShaderSourceYellow = "#version 330 core\n"
		"uniform vec3 uniformColor;" //прописываем униформу
		"out vec4 color;\n"
		"void main(){\n"
		"color = vec4(uniformColor, 1.0f);}\0";

	const GLchar* vertexShaderGradientSource = "#version 330 core\n"
		"in vec3 position;\n"
		"in vec3 color;\n"
		"out vec3 Color;\n"
		"void main(){\n"
		"Color = color;\n"
		"gl_Position = vec4(position, 0.0, 0.1);}\0";

	const GLchar* fragmentShaderGradientSource = "#version 330 core\n"
		"in vec3 Color;\n"
		"out vec4 outColor;\n"
		"void main(){\n"
		"outColor = vec4(Color, 1.0);}\0";




	const GLchar* vertexShaderLecture = "#version 330 core\n"
		"layout (location=0) in vec3 position;\n"
		"out vec4 vertexColor;\n"
		"void main(){\n"
		"gl_Position = vec4(position, 1.0);\n"		
		"vertexColor = vec4(1.0f, 0.4f, 0.3f, 1.0f);\n"
		"}\0";

	const GLchar* fragmentShaderLecture = "#version 330 core\n"
		"in vec4 vertexColor;\n"
		"out vec4 color;\n"
		"void main(){\n"
		"color = vertexColor;}\0";

	const GLchar* fragmentTestUniformShader = "#version 330 core\n"
		"out vec4 color;\n"
		"uniform vec4 outColor;\n"
		"void main(){\n"
		"color = outColor;}\0";


	const GLchar* gradientVertexShader = "#version 330 core\n"
		"#extension GL_ARB_explicit_uniform_location : require\n"
		"layout (location = 0) in vec3 position;\n"
		"layout (location = 1) in vec3 color;\n"		
		"out vec3 ourColor;\n"
		"void main(){\n"
		"gl_Position = vec4(position, 1.0);\n"
		"ourColor = color;}\0";
	const GLchar* gradientFragmentShader = "#version 330 core\n"
		"in vec3 ourColor;\n"
		"uniform vec3 flexColor;\n"
		"out vec4 color;\n"		
		"void main(){\n"		
		"color = vec4(ourColor.x+flexColor.x, ourColor.y+flexColor.y, ourColor.z+flexColor.z,1.0f);}\0";
	

	const GLchar* gradientVertexRotateShader = "#version 330 core\n"
		"#extension GL_ARB_explicit_uniform_location : require\n"
		"layout (location = 0) in vec3 position;\n"
		"layout (location = 1) in vec3 color;\n"
		"uniform vec2 rotation;\n"
		"uniform vec2 transfer;\n"
		"out vec3 ourColor;\n"
		"void main(){\n"
		"gl_Position = vec4(position.x*rotation.y - position.y*rotation.x + transfer.x, position.x*rotation.x + position.y*rotation.y + transfer.y, position.z, 1.0);\n"
		"ourColor = color;}\0";

	const GLchar* gradientVertexChangeColorShader = "#version 330 core\n"
		"#extension GL_ARB_explicit_uniform_location : require\n"
		"layout (location = 0) in vec3 position;\n"
		"layout (location = 1) in vec3 color;\n"
		"uniform vec2 rotation;\n"
		"uniform vec2 transfer;\n"
		"out vec3 ourColor;\n"
		"out vec4 trPosition;\n"
		"void main(){\n"
		"gl_Position = vec4(position.x*rotation.y - position.y*rotation.x + transfer.x, position.x*rotation.x + position.y*rotation.y + transfer.y, position.z, 1.0);\n"
		"trPosition = gl_Position;\n"
		"ourColor = color;}\0";
	const GLchar* gradientFragmentRotationChangeColorShader = "#version 330 core\n"		
		"uniform vec3 flexColor;\n"
		"in vec4 trPosition;"
		"out vec4 color;\n"
		"void main(){\n"
		"color = vec4(trPosition);}\0";


	const GLchar* textureVertexShader = "#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
		"layout (location = 1) in vec3 color;\n"
		"layout (location = 2) in vec2 texCoord;\n"
		"out vec3 ourColor;\n"
		"out vec2 TexCoord;\n"
		"uniform mat4 transform;"
		"void main(){\n"
		"gl_Position = transform * vec4(position, 1.0f);\n"
		"ourColor = color;\n"
		"TexCoord = vec2(texCoord.x, 1.0f-texCoord.y);}\n";
	const GLchar* textureFragmentShader = "#version 330 core\n"
		"in vec3 ourColor;\n"		
		"in vec2 TexCoord;\n"
		"out vec4 color;\n"
		"uniform sampler2D ourTexture1;\n"
		"uniform sampler2D ourTexture2;\n"
		"uniform float mixCoef;\n"
		"void main(){\n"					
		"color = mix(texture(ourTexture1, TexCoord)* vec4(ourColor, 1.0f), texture(ourTexture2, vec2(1.0f-TexCoord.x,TexCoord.y)) , mixCoef);}\n";
	
};

