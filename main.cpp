#define GLFW_INCLUDE_NONE
#include"glad.h"
#include<GLFW/glfw3.h>
#include<iostream>


const char* window_name = "hello world";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

float vertices[] = {
	 0.5f,  0.5f, 0.0f, //top right
	 0.5f, -0.5f, 0.0f, //bottom right
	-0.5f,  0.5f, 0.0f, //top left
	-0.5f, -0.5f, 0.0f, //bottom left
	 0.0f,  0.9f, 0.0f  //house roof top
};

unsigned int indices[] = {
	0, 1, 2,//first triangle
	2, 3, 1,//second triangle
	0, 2, 4	//roof
};

unsigned int indicesWF[] = {
	0, 1,
	0, 2,
	1, 2,
	2, 3,
	1, 3,
	0, 4,
	2, 4
};

const char *vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"out vec4 vertexColor;\n"
	"void main(){\n"
	"	gl_Position = vec4(aPos, 1.0);\n"
	"	vertexColor = vec4((aPos.x / 2) + 0.5f, (aPos.y / 2) + 0.5f, (aPos.z / 2) + 0.5f, 1.0);\n"
	"}\n";
unsigned int vertexShader;

const char *fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"in vec4 vertexColor;\n"
	"\n"
	"void main(){\n"
	"FragColor = vertexColor;\n"
	"}\n";
unsigned int fragmentShader;

unsigned int shaderProgram;

unsigned int VBO;
unsigned int VAO;
unsigned int EBO;
unsigned int EBOWF;

bool wireframe = false;

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
	
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &EBOWF);
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	//VAO
	glBindVertexArray(VAO);
	//VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//EBOWF
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOWF);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesWF), indicesWF, GL_STATIC_DRAW);
	
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
		if(!wireframe){		
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		}
		else{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOWF);
			glDrawElements(GL_LINES, 14, GL_UNSIGNED_INT, 0);	
		}
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

bool toggle = true;
void processInput(GLFWwindow *window){
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);
	}
	if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS){
		if(toggle == true){
			wireframe = !wireframe;
			toggle = false;
		}
	}
	else{toggle = true;}
}
