#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int windowWidth = 960;
int windowHeight = 720;

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

	//Create vertex shader object and reference, attach it to the shader source and compile
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//Create fragment shader object and reference, attach it to the shader source and compile
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//Create shader program object, attach vertex and fragment to the program and link them all together
	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//Delete the now useless shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


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


	GLuint VAO, VBO;
	
	//Generate VAO and VBO 
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind VAO as the current vertex array object
	glBindVertexArray(VAO);

	//Bind VBO as GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Configure Vertex attribute to read VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Bind VAO and VBO to 0 so that we don't modifity by accident
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	
	

	//Main loop
	while (!glfwWindowShouldClose(window))
	{
		//Background Color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//Clean back buffer and assign new color
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		//Event handling
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	//Delete widnow before ending the program
	glfwDestroyWindow(window);
	//Terminate GLFW
	glfwTerminate();
	return 0;
}