#include "Rotate.h"

Rotate::Rotate(float angle, float x, float y, float z) : angle(angle), axis(x, y, z)
{

}

glm::mat4 Rotate::getMatrix()
{
	return glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
}

