#include "Point.h"
#include "Program.h"

int main(int argc, char const *argv[])
{
    /* code */
       float vertices[] = {
        // positions
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    GLFWwindow* window;

    if (!glfwInit()||!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) )
        return -1;
    else window = glfwCreateWindow(1280,720,"DISCM SIM",NULL,NULL);
    Program prog = Program("foo","frag.glsl");
    if(!window){ glfwTerminate(); return -1;}
    glfwMakeContextCurrent(window);
    
    prog.use();
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        
    }
     glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
