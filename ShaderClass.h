#pragma once
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <string>
// TODO: Rewrite to a better structure.
class ShaderClass
{
private:
	GLuint shader;		

public:
	ShaderClass(std::string path, GLenum type);
	ShaderClass();

	GLuint getShader();
	// gets uniform location
	GLint findUloc(const GLchar *src);
};
