// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include <glad/glad.h>
#include "glfw/glfw3.h"
#include <vector>
#include "shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Renderer.h"


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
	glClearColor(0.3f, 0.2f, 0.5f, 1.0f);
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
		 0.5f,0.5f,
		-0.5f,0.5f
	};

	unsigned int indices[] = {
		0,1,2,
		0,3,2
	};
	
	//unsigned int VAO,VBO,EBO;

	//glGenVertexArrays(1, &VAO);
	//glBindVertexArray(VAO);

	//glGenBuffers(1, &VBO);
	//glBindBuffer(GL_ARRAY_BUFFER,VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(positions),positions,GL_STATIC_DRAW);

	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);


	//glEnableVertexAttribArray(0);
	
	Shader myshader("src/Shaders/default.vert","src/Shaders/default.frag");
	
	VertexArray va;
	VertexBuffer vb(positions,sizeof(positions));
	VertexBufferLayout layout;
	layout.push<float>(2);
	va.AddBuffer(vb, layout);
	IndexBuffer ib(indices, 6);
	Renderer renderer;

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		va.Bind();
		ib.Bind();
		myshader.Bind();
		renderer.Draw(va, ib,myshader);
		//glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}



