#include "Point.h"
#include "matrix_transform.hpp"

#include <glm/gtx/rotate_vector.hpp>
#include "include/standalone_math.h"
#define X_MAX 720
#define Y_MAX 1280
glm::vec3 Point::get_pos()
{
    return this->pos;
}
Point::Point(float x, float y, float s, float theta)
{
    this->pos = glm::vec3(x, y, 0);
    this->translate *= s;
    float cos = theta, sin = theta;
    glm::rotateZ(this->pos,glm::radians(theta));
    
    
    }
void Point::collide(){
    if(this->pos.x<=0)
    glm::reflect(this->pos,glm::vec3(0.f,1.f,0.f));
    
    if(this->pos.x>=X_MAX)glm::reflect(this->pos,glm::vec3(0.f,-1.f,0.f));
    
    if(this->pos.y>=Y_MAX)glm::reflect(this->pos,glm::vec3(1.f,0.f,0.f));
    
    if(this->pos.y<0)glm::reflect(this->pos,glm::vec3(-1.f,1.f,0.f));
}