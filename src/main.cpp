#define GLFW_INCLUDE_NONE
#include"../glad.h"
#include"shader.h"
#include"../stb_image.h"
#include<GLFW/glfw3.h>
#include<iostream>

#include<cmath>

const char* window_name = "hello world";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

float offset[2] = {0.0f, 0.0f};

float vertices[] = {
     0.5f, 0.5f,-0.5f,    1.0f, 1.0f, 0.0f,  1.0f, 1.0f,//top right
    -0.5f,-0.5f,-0.5f,    0.0f, 1.0f, 1.0f,  0.0f, 0.0f,//bottom left
     0.5f,-0.5f,-0.5f,    1.0f, 0.0f, 1.0f,  0.0f, 1.0f,//bottom right
    -0.5f, 0.5f, 0.5f,    1.0f, 1.0f, 0.0f,  1.0f, 0.0f,//top left
};

unsigned int indices[] = {
    0,1,2,
    0,3,1
};

unsigned int indicesWF[] = {
    0,1,
    0,2,
    1,2,
};

unsigned int VBO;
unsigned int VAO;
unsigned int EBO;
unsigned int EBOWF;

bool wireframe = false;

float windowSize[] = {800.0, 600.0, 1.0, 1.0};

int main(){
	if(!glfwInit()){
		std::cout << "failed to initialise GLFW";
		glfwTerminate();
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(
            windowSize[0], windowSize[1],
            window_name,
            NULL, NULL
    );
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
    Shader shader(
            "src/shaders/vertShader.vert",
            "src/shaders/fragShader.frag"
    );
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
	glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            sizeof(indices),
            indices,
            GL_STATIC_DRAW
    );
	//EBOWF
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOWF);
	glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            sizeof(indicesWF),
            indicesWF,
            GL_STATIC_DRAW
    );

	glVertexAttribPointer(
            0, 3,
            GL_FLOAT,
            GL_FALSE,
            8 * sizeof(float),
            (void*)0
    );
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
            1, 3,
            GL_FLOAT,
            GL_FALSE,
            8 * sizeof(float),
            (void*)(3 * sizeof(float))
    );
	glEnableVertexAttribArray(1);

    glVertexAttribPointer(
            2, 2,
            GL_FLOAT,
            GL_FALSE,
            8 * sizeof(float),
            (void*)(6 * sizeof(float))
    );
    glEnableVertexAttribArray(2);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("src/container.jpg", &width, &height, &nrChannels, 0);
    if(data){
        glTexImage2D(
                GL_TEXTURE_2D, 0,
                GL_RGB,
                width,
                height, 0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                data
        );
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cout << "failed to load texture" << std::endl;
        return -1;
    }


	while(!glfwWindowShouldClose(window)){
		processInput(window);

		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        shader.setVec2("offset", offset);
        shader.setVec4("windowSize", windowSize);
        glBindTexture(GL_TEXTURE_2D, texture);
	    shader.setSampler2D("Texture", 0);
        glBindVertexArray(VAO);
		if(!wireframe){
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glDrawElements(
                    GL_TRIANGLES,
                    sizeof(indices) / 4,
                    GL_UNSIGNED_INT,
                    0
            );
		}
		else{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOWF);
			glDrawElements(
                    GL_LINES,
                    sizeof(indicesWF) / 4,
                    GL_UNSIGNED_INT,
                    0
            );
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
	Shader shader(
            "src/shaders/vertShader.vert",
            "src/shaders/fragShader.frag"
    );
    (void)window;
	glViewport(0, 0, width, height);
    windowSize[0] = width;
    windowSize[1] = height;
    shader.setVec4("windowSize", windowSize);
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
        offset[0] += 2.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        offset[0] -= 2.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        offset[1] += 2.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        offset[1] -= 2.0f;
    }
}
