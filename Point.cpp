#include "Point.h"
#include "matrix_transform.hpp"

#include <glm/gtx/rotate_vector.hpp>
// #include "include/standalone_math.h"
#define X_MAX 1280
#define Y_MAX 720
glm::vec3 Point::get_pos() const
{
    return this->pos;
}
Point::Point(float x, float y, float s, float theta)
{
    this->pos = glm::vec3(x, y, 0);
    this->velo = glm::vec3(-1,0,0);
    // float cos = theta, sin = theta;
    glm::rotateZ(this->velo,glm::radians(theta));
    this->velo *=s;
    
    }
void Point::collide(){
    if (this->pos.x <=0 || this->pos.x >= X_MAX )
        this->pos.x = -this->pos.x ;
    if (this->pos.y <=0 || this->pos.y >= Y_MAX )
        this->pos.y = -this->pos.y ;
    
}
glm::vec3 Point::move(){

}