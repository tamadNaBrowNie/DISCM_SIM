#ifndef PROGRAM_H
#define PROGRAM_H
#include "ShaderClass.h"  
#include <string>
#include <GLFW/glfw3.h>
// Ensure this file is correctly defined and available
// CLASS THAT RUNS SHADERS
class Program {
private:
    GLuint prog;          // Program ID
    ShaderClass vert;     // Vertex shader
    ShaderClass frag;     // Fragment shader

    void create();        // Helper function to create the shader program

public:
    // Constructor that takes paths to the vertex and fragment shader files
    Program(std::string v_path, std::string f_path);
    
    // Constructor that takes ShaderClass objects for vertex and fragment shaders
    Program(ShaderClass vert, ShaderClass frag);
    
    // Method to use the shader program
    void use();
    
    // Getter for the fragment shader ID
    unsigned int getFrag();
    
    // Getter for the vertex shader ID
    unsigned int getVert();
};

#endif // PROGRAM_H
