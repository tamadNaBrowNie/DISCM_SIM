#include "Point.h"

glm::vec3 Point::get_pos()
{
    return this->pos;
}
Point::Point(float x, float y, float s, float theta)
{
    this->pos = glm::vec3(x, y, 0);
    this->translate *= s;
    glm::rotate(glm::mat4(1.f),10.f,glm::vec3(0,0,1));
    }
