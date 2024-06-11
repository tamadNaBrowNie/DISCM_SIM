#include "Point.h"
#include "matrix_transform.hpp"

#include <glm/gtx/rotate_vector.hpp>
#include "include/standalone_math.h"

#define X_MAX 1280
#define Y_MAX 720

// Constructor with position, speed, and angle
Point::Point(float x, float y, float s, float theta) {
    this->pos = glm::vec3(x, y, 0);
    float radians = glm::radians(theta);
    this->velocity = glm::vec2(s * cos(radians), s * sin(radians));
}

// Constructor with position and angle
Point::Point(glm::vec2 pos, float theta) {
    this->pos = glm::vec3(pos, 0);
    float radians = glm::radians(theta);
    // Assume a default speed of 1 if not specified
    this->velocity = glm::vec2(cos(radians), sin(radians));
}

// Constructor with a glm::vec4
Point::Point(glm::vec4 data) {
    this->pos = glm::vec3(data.x, data.y, 0);
    float radians = glm::radians(data.w);
    this->velocity = glm::vec2(data.z * cos(radians), data.z * sin(radians));
}

// Get the position of the point
glm::vec3 Point::get_pos() const {
    return this->pos;
}

// Move the point based on its velocity
glm::vec2 Point::move() {
    this->pos.x += this->velocity.x;
    this->pos.y += this->velocity.y;
    collide();
    return glm::vec2(this->pos.x, this->pos.y);
}

// Handle collisions with the canvas borders
void Point::collide() {
    if (this->pos.x <= 0 || this->pos.x >= X_MAX) {
        this->velocity.x = -this->velocity.x;
    }
    if (this->pos.y <= 0 || this->pos.y >= Y_MAX) {
        this->velocity.y = -this->velocity.y;
    }
}

// Set translation vector (placeholder, can be expanded as needed)
void Point::set_translate(glm::vec2 new_translate, float value) {
    this->translate = new_translate * value;
}

// Get the current translation vector
glm::vec2 Point::get_translate() const {
    return this->translate;
}

// Placeholder for hit detection (can be expanded as needed)
glm::vec3 Point::hit() {
    // Placeholder implementation
    return this->pos;
}
