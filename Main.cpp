
#include "Program.h"
#include "Point.h"
#include <vector>
#include <iostream>
#include <chrono>
#include <future>

// Keybinds for actions
enum Acts
{
    KILL =  GLFW_KEY_ESCAPE,
    dPOS = GLFW_KEY_P,
    dSPEED = GLFW_KEY_S,
    dTHETA = GLFW_KEY_T
};
// Screen
constexpr float X_MAX = 1280.f;
constexpr float Y_MAX = 720.f;

void Key_Callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    // TODO: MUTEX THIS
    if (action != GLFW_RELEASE)return;
    std::vector<Point*>* arr = (std::vector<Point*> *)glfwGetWindowUserPointer(window);

    float x_pos = 0, y_pos = 0, s = 0, deg = 0;

    auto hl = [&](int T, int n){
        
        float start = 0 ,end = 0;

        
        auto push = [&](float* f) {

            std::cin >> x_pos;
            std::cin >> y_pos;
            float d = (end - start) / (float)n;
            *f = start;
            for (int i = 0; i < n; i++) {

                arr->push_back(new Point(x_pos, y_pos, s, deg));
                *f += d;
                
            }

            };
        switch (T) {
        case Acts::dPOS:
            break;
        case Acts::dSPEED:
            std::cin >> deg;
            std::cin >> start;
            std::cin >> end;

            push(&s);
            break;

        case Acts::dTHETA:
            std::cin >> s;
            std::cin >> start;
            std::cin >> end;
            
            push(&deg);
            break;
        default: std::cerr << "HOW TF";
        }
        
        
    };
    
        switch (key)
        {
        case Acts::dPOS:
            
        case Acts::dSPEED:
          
        case Acts::dTHETA:
            
            
            std::cout << "n = ";
            hl(key, std::cin.get());
            
            
           
            
            break;
           
        case Acts::KILL:
            // KILL WINDOW
            glfwSetWindowShouldClose(window, true);
            break;

        default:;
        }
    
}

int main(int argc, char const *argv[])
{
    /* code */
    float vertices[] = {
        // positions
        10.f, -10.f
        };
    GLFWwindow *window = nullptr;
    GLenum init = glfwInit();

    if ( init == GLFW_FALSE)
    {
        std::cout << "glfw failed";
        return -1;
    }   
    window = glfwCreateWindow(X_MAX, Y_MAX, "DISCM SIM", NULL, NULL);
    if (!window)
    {
        std::cout << "no window";
        glfwTerminate();
        return -1;
    }
    glfwSetKeyCallback(window, Key_Callback);
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
    int width  =0, height =0;
    glEnable(GL_PROGRAM_POINT_SIZE);
    glPointSize(10.f);
    constexpr double TIC = 16.6666666667;

    double last_tic = glfwGetTime() * 1000.f, new_tic = glfwGetTime() * 1000.f,dt =0;
    std::vector<Point*> arr;
    glfwSetWindowUserPointer(window, &arr);
    while (!glfwWindowShouldClose(window))
    {

            new_tic = glfwGetTime() * 1000.f;
            dt = new_tic - last_tic;
            glfwGetWindowSize(window, &width, &height);
            glad_glViewport(0, 0, width, height);
            glClear(GL_COLOR_BUFFER_BIT);
            // glDrawArraysInstanced(GL); //TODO: try to make it instanced
            prog.use();
            if (TIC <= dt)
            {
                //std::cout << "I AM FUCKING INVINCIBLE";
                //PUT BOING HERE
            }
            glBindVertexArray(VAO);
            glDrawArrays(GL_POINTS, 0, 2);
            glfwSwapBuffers(window);
           
        
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}


