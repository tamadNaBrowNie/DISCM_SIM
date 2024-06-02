#include "Program.h"
void Program::create()
{
    this->prog = glCreateProgram();
    glAttachShader(this->prog, vert.getShader());
    glAttachShader(this->prog, frag.getShader());
    glLinkProgram(this->prog);
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
unsigned int Program::getFrag()
{
    return this->frag.getShader();
}
unsigned int Program::getVert()
{
    return this->vert.getShader();
}
