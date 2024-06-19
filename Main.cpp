#include "Program.h"
#include "Point.h"
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

// Keybinds for actions
enum Acts
{
    KILL = GLFW_KEY_ENTER,
    DATA = GLFW_KEY_ESCAPE,
    ADD = GLFW_KEY_SPACE
};

// Screen dimensions
constexpr float X_MAX = 1280.f;
constexpr float Y_MAX = 720.f;

std::vector<Point> particles;
std::mutex particlesMutex;

void Key_Callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS) {
        switch (key)
        {
        case Acts::DATA:
            std::cout << "waiting?";
            std::cin.get();
            std::cout << "waiting";
            break;
        case Acts::KILL:
            glfwSetWindowShouldClose(window, true);
            break;
        case Acts::ADD:
            // Add particles at a specific position with specific velocity and angle
            std::cout << "Adding particles\n";
            {
                std::lock_guard<std::mutex> lock(particlesMutex);
                for (int i = 0; i < 10; ++i) {
                    particles.emplace_back(100.f, 100.f, 50.f, 45.f); // Example values
                }
            }
            break;
        default:
            break;
        }
    }
}

void updateParticles(float deltaTime) {
    std::lock_guard<std::mutex> lock(particlesMutex);
    for (auto& particle : particles) {
        particle.move(deltaTime);
    }
}

void renderParticles() {
    std::lock_guard<std::mutex> lock(particlesMutex);
    for (const auto& particle : particles) {
        glm::vec3 pos = particle.get_pos();
        // Draw particle at pos.x, pos.y
        // Implement your drawing logic here
    }
}

int main(int argc, char const *argv[])
{
    float vertices[] = {
        0.f, 0.f
    };

    GLFWwindow *window = nullptr;
    GLenum init = glfwInit();

    if (init == GLFW_FALSE)
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

    Program prog = Program("vert.glsl", "frag.glsl");

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

    int width = 0, height = 0;
    glEnable(GL_PROGRAM_POINT_SIZE);
    glPointSize(5.f);

    auto lastTime = std::chrono::high_resolution_clock::now();
    auto lastFpsTime = std::chrono::high_resolution_clock::now();
    int frameCount = 0;
    float fps = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        glfwGetWindowSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        prog.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, 2);
        glfwSwapBuffers(window);
        glfwPollEvents();

        frameCount++;
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastFpsTime).count();
        if (elapsedTime >= 500)
        {
            fps = frameCount / (elapsedTime / 1000.0f);
            frameCount = 0;
            lastFpsTime = currentTime;
            std::cout << "FPS: " << fps << std::endl;
        }

        float deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count() / 1000.0f;
        lastTime = currentTime;

        updateParticles(deltaTime);
        renderParticles();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}