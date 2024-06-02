
#include "ShaderClass.h"

// gets uniform location

ShaderClass::ShaderClass(std::string path, GLenum type)
{
	// TODO:speed this up. maybe rewrite.
	// TODO: Error Checking
	std::fstream vertSrc(path);
	std::stringstream vertBuff;
	vertBuff << vertSrc.rdbuf();
	std::string vertS = vertBuff.str();
	const char *v = vertS.c_str();

	// Compile shader
	this->shader = glCreateShader(type);
	glShaderSource(this->shader, 1, &v, NULL);
	glCompileShader(this->shader);
}
GLuint ShaderClass::getShader()
{
	return this->shader;
}

GLint ShaderClass::findUloc(const GLchar *src)
{
	GLint unif = glGetUniformLocation(this->shader, src);

	return unif;
}
