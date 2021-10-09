#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

using namespace std;

string get_file_contents(const char* filename);

class shader
{
public:
	GLuint shaderProgram;
	shader(const char* vetrex, const char* fragment);
	void Activate();
	void Delete();
};

#endif