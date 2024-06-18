
#include "Program.h"
#include "Point.h"
#include <vector>
#include <iostream>
// Keybinds for actions
enum Acts
{
    KILL = GLFW_KEY_ENTER,
    DATA = GLFW_KEY_ESCAPE,
    ADD = GLFW_KEY_SPACE
};
// Screen
constexpr float X_MAX = 1280.f;
constexpr float Y_MAX = 720.f;

void Key_Callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    float x_pos = 0, y_pos = 0, s = 0, deg = 0;
    // TODO: MUTEX THIS
  /*std::vector<Point>* arr = (std::vector<Point> *)glfwGetWindowUserPointer(window);
    switch (key)
    {
    case Acts::DATA:
        // TODO: HANDLE BALL INPUT
        break;
    case Acts::KILL:
        // KILL WINDOW
        glfwSetWindowShouldClose(window, true);
        break;
    case Acts::ADD:
        // CREATES INSTANCE OF BALLS
        arr->push_back(Point(x_pos, y_pos, s, deg));
        break;
    default:;
    }*/  
}
int main(int argc, char const *argv[])
{
    /* code */
    float vertices[] = {
        // positions
        -0.01f, -0.01f,
        0.01f, -0.01f, 
        0.0f, 0.01f, 
        0.f, 0.f};
    GLFWwindow *window = nullptr;
    GLenum init = glfwInit();

    if ( init == GLFW_FALSE)
    {
        std::cout << "glfw failed";
        return -1;
    }   
    window = glfwCreateWindow(1280, 720, "DISCM SIM", NULL, NULL);
    if (!window)
    {
        std::cout << "no window";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    
    Program prog = Program("vert.glsl", "frag.glsl");//TODO now create a vertex shader file
    
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, X_MAX, Y_MAX, 0.0f, 0.f, 1.f);


    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        // glDrawArraysInstanced(GL); //TODO: try to make it instanced
        prog.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        //glCullFace(GL_FRONT);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
