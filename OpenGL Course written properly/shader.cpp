#include<iostream>
#include<glad/glad.h>
#include<fstream>
#include<sstream>
#include<cerrno>
#include<string>
#include "shader.h"


string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}
shader::shader(const char* vetrex, const char* fragment)
{
	std::string vertexSource = get_file_contents(vetrex);
	std::string fragmentSource = get_file_contents(fragment);

	const char* vertexShaderSource = vertexSource.c_str();
	const char* fragmentShaderSource = fragmentSource.c_str();
	
	//creation of a vertex shader
	GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexshader, 1, &vertexShaderSource, NULL); //vertexshader object, number of srtings, shader code random
	glCompileShader(vertexshader);

	//creation of a fragment shader
	GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader, 1, &fragmentShaderSource, NULL); //vertexshader object, number of srtings, shader code random
	glCompileShader(fragmentshader);

	// make a shader program to add it up and use in a shader program
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexshader);
	glAttachShader(shaderProgram, fragmentshader);
	glLinkProgram(shaderProgram);

	// to keep it clean we delete the shaders
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);
}
void shader::Activate()
{
	glUseProgram(shaderProgram);
}
void shader::Delete()
{
	glDeleteProgram(shaderProgram);
}
