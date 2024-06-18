
#include "ShaderClass.h"

#include <iostream>
// CLASS FOR LOADING SHADERS
// gets uniform location

ShaderClass::ShaderClass(std::string path, GLenum type):shader(glCreateShader(type))
{
	// TODO:speed this up. maybe rewrite.
	// TODO: Error Checking

	std::ifstream shaderFile(path);
    if (!shaderFile.is_open()) {
        std::cerr << "Failed to open shader file: " << path << std::endl;
        return;
    }
	std::fstream vertSrc(path);
	std::stringstream vertBuff;
	vertBuff << vertSrc.rdbuf();
	std::string vertS = vertBuff.str();
	const char* v = vertS.c_str();
	// Compile shader
	glShaderSource(this->shader, 1, &v, NULL);
	

	glCompileShader(this->shader);
	// Check for errors
	 GLint success;
    glGetShaderiv(this->shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(this->shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

ShaderClass::ShaderClass()
{
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
