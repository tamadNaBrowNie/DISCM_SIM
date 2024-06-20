#include "Point.h"
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
// #include "include/standalone_math.h"

glm::vec3 Point::get_pos() const
{
    return this->pos;
}
Point::Point(float x, float y, float s, float theta)
{
    this->pos = glm::vec3(x, y, 0);
    this->velo = glm::vec3(-1, 0, 0);
    // float cos = theta, sin = theta;
    glm::rotateZ(this->velo, glm::radians(theta));
    this->velo *= s;
}
void Point::collide(float X_MAX, float Y_MAX)
{
    if (this->pos.x <= 0 || this->pos.x >= X_MAX)
        this->pos.x = -this->pos.x;
    if (this->pos.y <= 0 || this->pos.y >= Y_MAX)
        this->pos.y = -this->pos.y;
}
