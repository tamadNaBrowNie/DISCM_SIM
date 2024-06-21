
#include "Program.h"
#include "Point.h"
#include <vector>
#include <iostream>
#include <chrono>
#include <future>
#include <glm/gtc/matrix_transform.hpp>
#include "TextRenderer.h"
#include <glm/gtc/type_ptr.hpp>
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



    auto hl = [&arr,key]( ){
        float x_pos = 0, y_pos = 0, s = 0, deg = 0;
        float start = 0 ,end = 0;
        int n = 1;
        
        auto push = [&](float* f) {
            std::cout << "n = ";
            std::cin >> x_pos;
            std::cin >> y_pos;
            float d = (end - start) / (float)n;
            *f = start;
            for (int i = 0; i < n; i++) {

                arr->push_back(new Point(x_pos, y_pos, s, deg));
                *f += d;
                
            }

            };
        switch (key) {
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
            
            
            //std::async(std::launch::async, hl);
            
            
           
            
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
        0.f, 10.f, 
    
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
    
    Program prog("vert.glsl", "frag.glsl");//TODO now create a vertex shader file
    
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
   
    int width  =0, height =0;
    glEnable(GL_PROGRAM_POINT_SIZE);
    glPointSize(10.f);
    constexpr double TIC = 16.6666666667;

    prog.use();
    std::cout<<glGetUniformLocation(prog.getVert(),"v");
    glm::mat4 proj = glm::ortho(0.f, X_MAX, 0.f, Y_MAX);
    glm::mat4 cam = glm::lookAt(glm::vec3(X_MAX/2, Y_MAX / 2, 10), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
    glUniformMatrix4fv(3, 1, false, (const float*)glm::value_ptr(proj));
    glUniformMatrix4fv(4, 1, false, (const float*)glm::value_ptr(cam));
    std::cout <<"v: "<< glGetUniformLocation(prog.getVert(), "v");
    Program ctr("fps_v.glsl", "fps_frag.glsl");
    //TextRenderer textRenderer(X_MAX, Y_MAX);
    //textRenderer.Load("font/font.ttf", 24); // Replace with the path to your font file
    
    std::vector<Point*> arr;
    glfwSetWindowUserPointer(window, &arr);
    auto lastTime = std::chrono::high_resolution_clock::now();
    auto lastFpsTime = std::chrono::high_resolution_clock::now();
    int frameCount = 0;
    float fps = 0.0f;
    double last_tic = glfwGetTime() * 1000.f, new_tic = glfwGetTime() * 1000.f, dt = 0; 

    glm::mat4 tran = glm::translate(glm::mat4(1.0f), glm::vec3(2, 2, 0));
    float x = -0.1, y = -0.1;
    
    while (!glfwWindowShouldClose(window)){

        glfwGetWindowSize(window, &width, &height);
        glad_glViewport(0, 0, width, height);

        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
            // glDrawArraysInstanced(GL); //TODO: try to make it instanced
            prog.use();
        
            new_tic = glfwGetTime() * 1000.f;
            dt = new_tic - last_tic;
            float i = 0.01;

            glBindVertexArray(VAO);
            glUniformMatrix4fv(2, 1, false, (const float*)glm::value_ptr(tran));
            if (TIC <= dt)
            {
                last_tic = new_tic;

                
                
                tran *= glm::translate(glm::mat4(1.f), glm::vec3(x, y, 0.f));;
                
                std::cout << tran[3][1] << std::endl;
                if (tran[3][1] < 0.f|| tran[3][1] >2.f ) {
                    y = -y;
                    
                }
                if (tran[3][0] < 0.f || tran[3][0] >2.f) {
                    x = -x;

                }
                //PUT BOING HERE
            }

            glDrawArrays(GL_POINTS, 0, 1);


            

           // glDrawArrays(GL_POINTS, 0, 1);
     


            auto lastTime = std::chrono::high_resolution_clock::now();
            auto lastFpsTime = std::chrono::high_resolution_clock::now();
            int frameCount = 0;
            float fps = 0.0f;
           //ctr.use();
          //  textRenderer.RenderText("FPS: " + std::to_string(fps), 10.0f, 10.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
     
            glfwSwapBuffers(window);
   

            glBindVertexArray(0);
        
        
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}


