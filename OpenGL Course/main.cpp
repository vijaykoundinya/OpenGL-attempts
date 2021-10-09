#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
using namespace std;

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

		//creation of a vertex shader
	GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexshader, 1, &vertexShaderSource, NULL); //vertexshader object, number of srtings, shader code random
	glCompileShader(vertexshader);

	//creation of a fragment shader
	GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader, 1, &fragmentShaderSource, NULL); //vertexshader object, number of srtings, shader code random
	glCompileShader(fragmentshader);

	// make a shader program to add it up and use in a shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexshader);
	glAttachShader(shaderProgram, fragmentshader);
	glLinkProgram(shaderProgram);

	// to keep it clean we delete the shaders
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);

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

	GLuint indecies[] = { 0,3,5,
	3,2,4,
	5,4,1 };
	GLuint VAO, VBO, EBO; //generally an array . ALSO VAO before VBO
	glGenVertexArrays(1, &VAO); // the number of VBOs and the reference of the VBO
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // binding, it informs the buffer that this is variable to be used when we call a function to modify the variable
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // this last can be static stream dynamic bepending on the number of times it can be modified or used
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indecies), indecies,GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); 	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glEnableVertexAttribArray(0);// enable it and point to 0
	
								 
	//unbind by binding to 0 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//holding the window open unit something closes it.
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.6f, 0.3f, 1.0f); // it is in the normalised RGB form and transparency.
		glClear(GL_COLOR_BUFFER_BIT); //current buffer
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents(); //proccesses all the events 
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	glfwTerminate();
	return 0;
}