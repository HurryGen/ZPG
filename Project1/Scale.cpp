#include "Scale.h"

Scale::Scale(float x, float y, float z) : scaling(x, y, z)
{
}

glm::mat4 Scale::getMatrix() const
{
	return glm::scale(glm::mat4(1.0f), scaling);
}
