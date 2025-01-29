#define GLFW_INCLUDE_NONE
#include"glad.h"
#include<GLFW/glfw3.h>
#include<iostream>


const char* window_name = "hello world";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

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
	
	while(!glfwWindowShouldClose(window)){
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width, height);
}
