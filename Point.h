
#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
enum type
{
    VECTOR,
    MOVE
};
class Point
{
private:
    glm::vec2 translate, pos;
    glm::vec2 change(float, float);
    glm::vec2 move();

public:
    Point(glm::vec2, type);
    Point(float, float, type);
    void set_translate(float, float, type);
    void set_translate(glm::vec2, type);
    void get_translate();
    glm::vec2 get_translate(type);
    glm::vec2 get_pos();
};
