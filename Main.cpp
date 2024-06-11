#include "Point.h"
#include "Program.h"

int main(int argc, char const *argv[])
{
    /* code */
    GLFWwindow* window;
    if (!glfwInit() )
    return -1;
    else window = glfwCreateWindow(1280,720,"DISCM SIM",NULL,NULL);
    Program frag = Program("foo","bar");
    if(!window){ glfwTerminate(); return -1;}
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        
    }
    
    return 0;
}
