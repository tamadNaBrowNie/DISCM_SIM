#include "Point.h"
#include "matrix_transform.hpp"


glm::vec3 Point::get_pos()
{
    return this->pos;
}
Point::Point(float x, float y, float s, float theta)
{
    this->pos = glm::vec3(x, y, 0);
    this->translate *= s;
    float cos = theta, sin = theta;
    glm::mat4 spinner =glm::mat4(cos,sin,-sin,cos);
    glm::rotate(spinner,10.f,glm::vec3(0,0,1));
    translate *= spinner;
    
    }
