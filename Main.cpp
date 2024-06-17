
#include "Program.h"
#include "Point.h"
#include <vector>
float x_pos = 0, y_pos = 0, s = 0, deg = 0;
void Key_Callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    std::vector<Point> *arr = (std::vector<Point> *)glfwGetWindowUserPointer(window);
    switch (key)
    {
    case GLFW_KEY_ESCAPE:
        // TODO: This is where we handle user inputs for balls
        break;
    case GLFW_KEY_ENTER:

        glfwSetWindowShouldClose(window, true);
        break;
    case GLFW_KEY_SPACE:
        arr->push_back(Point(x_pos, y_pos, s, deg));
        break;
    default:
        break;
    }
}
int main(int argc, char const *argv[])
{
    /* code */
    float vertices[] = {
        // positions
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.f, 0.f, -0.5f, 0.f};
    GLFWwindow *window = nullptr;

    if (!glfwInit() || !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return -1;
    else
        window = glfwCreateWindow(1280, 720, "DISCM SIM", NULL, NULL);
    Program prog = Program("foo", "frag.glsl");
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    prog.use();
    GLuint *VBO, *VAO;
    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);

    glBindVertexArray(*VAO);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    constexpr float X_MAX = 1280.f;
    constexpr float Y_MAX = 720.f;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, X_MAX, Y_MAX, 0.0f, 0.f, 1.f);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        // glDrawArraysInstanced(GL); //TODO: try to make it instanced
        prog.use();
        glBindVertexArray(*VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays(1, VAO);
    glDeleteBuffers(1, VBO);

    glfwTerminate();
    return 0;
}
