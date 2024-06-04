
#pragma once
// #include "include/glad/glad.h"
#include "include/glm/glm.hpp"
#include "include/GLFW/glfw3.h"
class Point
{
private:
    glm::vec2 translate = {-1,0};
    glm::vec3 pos;
    glm::vec2 move();


public:
    glm::vec3 hit();
    Point(glm::vec2 pos, float theta);
    Point(float x , float y,float speed, float theta );
    void collide();
    Point(glm::vec4 data);
    void set_translate(glm::vec2, float);
    void get_translate();
    
    glm::vec3 get_pos();
};
