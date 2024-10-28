#include "Translate.h"

Translate::Translate(float x, float y, float z) : translation(x, y, z)
{
}

glm::mat4 Translate::getMatrix() const
{
	return glm::translate(glm::mat4(1.0f), translation);
}
