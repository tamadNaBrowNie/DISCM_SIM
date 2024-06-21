#include "Program.h"
#include <iostream>
void Program::create()
{
    this->prog = glCreateProgram();
    glAttachShader(this->prog, vert.getShader());
    glAttachShader(this->prog, frag.getShader());
    glLinkProgram(this->prog);

    // Check for linking errors
    GLint success;
    glGetProgramiv(this->prog, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(this->prog, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}

Program::Program(std::string v_path, std::string f_path) : vert(v_path, GL_VERTEX_SHADER), frag(f_path, GL_FRAGMENT_SHADER)
{
    create();
}
Program::Program(ShaderClass vert, ShaderClass frag)
{
    this->vert = vert;
    this->frag = frag;
    create();
}
void Program::use()
{
    glUseProgram(this->prog);
}
ShaderClass Program::getFShad() {
    return this->frag;
}
ShaderClass Program::getVShad() {
    return this->vert;
}
unsigned int Program::getFrag()
{
    return this->frag.getShader();
}
unsigned int Program::getVert()
{
    return this->vert.getShader();
}
unsigned int Program::getProg() {
    return this->prog;
}
