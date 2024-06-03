
#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
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
    Point(glm::vec4 data);
    void set_translate(glm::vec2, float);
    void get_translate();
    
    glm::vec3 get_pos();
};
