#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "shader.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
using namespace std;


int main()
{
	//intialization functions
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);


	//creation of window
	GLFWwindow* window = glfwCreateWindow(800, 800, "trial", NULL, NULL); //length hieght name fullscreen random
	if (window == NULL)
	{
		cout << "Trial failed" << "\n" << "window failed to create";
		glfwTerminate();
		return -1;
	}	
	glfwMakeContextCurrent(window);

	//glad using opengl
	gladLoadGL();
	glViewport(0, 0, 800, 800); // bottom right to top left.
	shader shaders = shader("default.vert","default.frag");
	//Triangle fake coordinates
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
		- 0.5f/2, -0.5f * float(sqrt(3)) / 6, 0.0f, // Lower left corner
		0.5f/2, -0.5f * float(sqrt(3)) / 6, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) / 3, 0.0f // Upper corner
	};

	GLuint indices[] = { 0,3,5,
	3,2,4,
	5,4,1 };
	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO to VAO
	VAO1.LinkVBO(VBO1, 0);
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	//holding the window open unit something closes it.
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.6f, 0.3f, 1.0f); // it is in the normalised RGB form and transparency.
		glClear(GL_COLOR_BUFFER_BIT); //current buffer
		shaders.Activate();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents(); //proccesses all the events 
	}
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaders.Delete();
	glfwTerminate();
	return 0;
}