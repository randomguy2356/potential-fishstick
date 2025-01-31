#define GLFW_INCLUDE_NONE
#include"../glad.h"
#include"shader.h"
#include<GLFW/glfw3.h>
#include<iostream>

#include<cmath>

const char* window_name = "hello world";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

double xoffset = 0.0f;
double yoffset = 0.0f;

float vertices[] = {
     0.0f,  0.5f,  0.0f,   1.0f, 0.0f, 0.0f, //triangle top red
    -0.5f, -0.5f,  0.0f,   0.0f, 1.0f, 0.0f, //triangle bottom left green
     0.5f, -0.5f,  0.0f,   0.0f, 0.0f, 1.0f  //triangle bottom right blue
};

unsigned int indices[] = {
    0,1,2
};

unsigned int indicesWF[] = {
    0,1,
    0,2,
    1,2
};

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
    Shader shader("src/shaders/vertShader.vert", "src/shaders/fragShader.frag");
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	while(!glfwWindowShouldClose(window)){
		processInput(window);

		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        shader.setFloat("xoffset", (float)xoffset);
        shader.setFloat("yoffset", (float)yoffset);

		glBindVertexArray(VAO);
		if(!wireframe){
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		}
		else{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOWF);
			glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, 0);
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
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
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        xoffset += 5.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        xoffset -= 5.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        yoffset += 5.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        yoffset -= 5.0f;
    }
}
