#pragma once

#include "include/glm/glm.hpp"
#include "include/GLFW/glfw3.h"

class Point {
private:
    glm::vec3 pos; // Position of the point
    glm::vec2 velocity; // Velocity vector
    glm::vec2 translate = {-1, 0}; // Translation vector (for future use)

    glm::vec2 move(); // Method to update the position based on velocity

public:
    // Constructors
    Point(glm::vec2 pos, float theta);
    Point(float x, float y, float speed, float theta);
    Point(glm::vec4 data);

    // Method to handle collision with canvas borders
    void collide();

    // Getter for position
    glm::vec3 get_pos() const;

    // Method to update translation (for future use)
    void set_translate(glm::vec2 new_translate, float value);

    // Method to get current translation (for future use)
    glm::vec2 get_translate() const;

    // Method to handle hit detection (for future use)
    glm::vec3 hit();
};

