#include "DynamicRotate.h"

DynamicRotate::DynamicRotate(float speed, float x, float y, float z) : Rotate(0.0f, x, y, z)
{
	this->speed = speed;
}

glm::mat4 DynamicRotate::getMatrix() 
{
	this->angle += speed;
	if (this->angle >= 360.0f) {
		this->angle = 0.0f;
	}
    return glm::rotate(glm::mat4(1.0f), glm::radians(this->angle), this->axis);
}
