#include<iostream>
#include <glad/glad.h>
#include"glfw/glfw3.h"


int main() {
	
	glfwInit();

	if (!glfwInit()) {
		std::cout << "glfw not initiated" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "VictorGordonOpenGl", NULL, NULL);
	if (!window) {
		std::cout << "window not created" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);
	glClearColor(0.2f, 0.3f, 5.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	

	/*float positions[] = {
		-0.5f,-0.5f,0.0f,0.0,
		0.5f,-0.5f,1.0f,0.0f,
		0.5f,0.5f,1.0f,1.0f,
	   -0.5f,0.5f,0.0f,1.0f
	};*/


	float positions[] = {
		-0.5f,-0.5f,
		 0.5f,-0.5f,
		 0.0f,0.5f	  
	};
	
	unsigned int VAO,VBO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions),positions,GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window)) {
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 4);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}



