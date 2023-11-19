#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"

int windowWidth = 960;
int windowHeight = 720;

//Create square vertice coordinates
GLfloat vertices[] =
{
	// First triangle (bottom-left, top-left, top-right)
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.5f,  0.5f, 0.0f,

	 // Second triangle (bottom-left, top-right, bottom-right)
	 -0.5f, -0.5f, 0.0f,
	  0.5f,  0.5f, 0.0f,
	 -0.5f,  0.5f, 0.0f
};

int main()
{
	// Initialize GFLW
	glfwInit();

	// OpenGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//CORE profile (modern functions)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a window called "OpenGL Kart"
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "OpenGL Kart", NULL, NULL);
	//Checks if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Makes window the current context
	glfwMakeContextCurrent(window);

	//loads glad 
	gladLoadGL();

	//Configures OpenGL viewport in the window
	glViewport(0, 0, windowWidth, windowHeight);


	//Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));

	// Links VBO to VAO
	VAO1.LinkVBO(VBO1, 0);
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	

	//Main loop
	while (!glfwWindowShouldClose(window))
	{
		//Background Color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//Clean back buffer and assign new color
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		VAO1.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		//Event handling
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	shaderProgram.Delete();

	//Delete widnow before ending the program
	glfwDestroyWindow(window);
	//Terminate GLFW
	glfwTerminate();
	return 0;
}