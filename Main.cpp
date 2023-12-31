#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include"Texture2D/Texture/Texture.h"
#include"Shaders/shaderClass.h"
#include"Texture2D/VAO/VAO.h"
#include"Texture2D/VBO/VBO.h"
#include"Texture2D/EBO/EBO.h"

int windowWidth = 960;
int windowHeight = 720;

// Vertices coordinates
GLfloat verticesLogo[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.6f,  0.2f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
	-0.6f,  0.55f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
	 0.6f,  0.55f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
	 0.6f,  0.2f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
};

GLfloat verticesStart[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.4f, -0.40f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
	-0.4f,  -0.24f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
	 0.4f,  -0.24f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
	 0.4f, -0.40f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
};

GLfloat verticesExit[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.35f, -0.64f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
	-0.35f, -0.48f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
	 0.35f, -0.48f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
	 0.35f, -0.64, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
};

// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1, // Upper triangle
	0, 3, 2 // Lower triangle
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
	Shader shaderProgram("Shaders/default.vert", "Shaders/default.frag");

	//Start button
	// 
	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(verticesStart, sizeof(verticesStart));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));
	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Texture
	Texture startTexture("Assets/Textures/Menu/start.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	startTexture.texUnit(shaderProgram, "tex0", 0);

	//Exit button
	// 
	// Generates Vertex Array Object and binds it
	VAO VAO2;
	VAO2.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO2(verticesExit, sizeof(verticesExit));
	// Generates Element Buffer Object and links it to indices
	EBO EBO2(indices, sizeof(indices));
	// Links VBO attributes such as coordinates and colors to VAO
	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();

	// Texture
	Texture exitTexture("Assets/Textures/Menu/exit.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	exitTexture.texUnit(shaderProgram, "tex0", 0);

	//Logo
	// 
	// Generates Vertex Array Object and binds it
	VAO VAO3;
	VAO3.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO3(verticesLogo, sizeof(verticesLogo));
	// Generates Element Buffer Object and links it to indices
	EBO EBO3(indices, sizeof(indices));
	// Links VBO attributes such as coordinates and colors to VAO
	VAO3.LinkAttrib(VBO3, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO3.LinkAttrib(VBO3, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO3.LinkAttrib(VBO3, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO3.Unbind();
	VBO3.Unbind();
	EBO3.Unbind();

	// Texture
	Texture logoTexture("Assets/Textures/Menu/logo.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	logoTexture.texUnit(shaderProgram, "tex0", 0);

	//Main loop
	while (!glfwWindowShouldClose(window))
	{
		//Background Color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//Clean back buffer and assign new color
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);
		startTexture.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		exitTexture.Bind();
		VAO2.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		logoTexture.Bind();
		VAO3.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		//Closes window with escape
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}

		//Event handling
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	startTexture.Delete();
	VAO2.Delete();
	VBO2.Delete();
	EBO2.Delete();
	exitTexture.Delete();
	VAO3.Delete();
	VBO3.Delete();
	EBO3.Delete();
	logoTexture.Delete();
	shaderProgram.Delete();

	//Delete window before ending the program
	glfwDestroyWindow(window);
	//Terminate GLFW
	glfwTerminate();
	return 0;
}