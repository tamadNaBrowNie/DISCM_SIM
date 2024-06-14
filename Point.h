#pragma once

#include "include/glm/glm.hpp"
#include "include/GLFW/glfw3.h"

class Point
{
private:
    float theta = 0.f;
    glm::vec3 pos; // Position of the point
    // glm::vec2 velocity; // Velocity vector
    glm::vec3 velo = {-1, 0, 0}; // Translation vector (for future use)

public:
    glm::vec3 move(); // Method to update the position based on 2city
    // Constructors
    Point(glm::vec2 pos, float theta);
    Point(float x, float y, float speed, float theta);
    void collide(float X_MAX, float Y_MAX);
    Point(glm::vec4 data);

    // Method to handle collision with canvas borders
    void collide();

    // void NewFunction();

    // Getter for position
    glm::vec3 get_pos() const;

    // Method to update translation (for future use)
    void set_translate(glm::vec2 new_translate, float value);

    // Method to get current translation (for future use)
    glm::vec2 get_translate() const;

    // Method to handle hit detection (for future use)
    glm::vec3 hit();
};
