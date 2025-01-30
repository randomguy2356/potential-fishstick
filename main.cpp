#define GLFW_INCLUDE_NONE
#include"glad.h"
#include<GLFW/glfw3.h>
#include<iostream>


const char* window_name = "hello world";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};

const char *vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main(){\n"
	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\n";
unsigned int vertexShader;

const char *fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"\n"
	"void main(){\n"
	"FragColor = vec4(0.0f, 0.8f, 0.8f, 0.5f);\n"
	"}\n";
unsigned int fragmentShader;

unsigned int shaderProgram;

unsigned int VBO;
unsigned int VAO;
int main(){
	if(!glfwInit()){
		std::cout << "failed to initialise GLFW";
		glfwTerminate();
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(800, 600, window_name, NULL, NULL);
	if(window == NULL){
		std::cout << "failed to create window" << '\n';
		std::cout << window << '\n';
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent( window );
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	shaderProgram = glCreateProgram();
	
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	while(!glfwWindowShouldClose(window)){
		processInput(window);
	
		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
	(void)window;
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window){
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);
	}
}
