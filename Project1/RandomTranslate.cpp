#include "RandomTranslate.h"
#include <GLFW/glfw3.h>

RandomTranslate::RandomTranslate(float speed, float x, float y, float z) : Translate(x, y, z)
{
	lowerBoundX = -1.f;
	upperBoundX = 1.f;
	lowerBoundY = -1.f;
	upperBoundY = 1.f;
	lowerBoundZ = -1.f;
	upperBoundZ = 1.f;
	lastUpdateTime = 0.0f;
	this->speed = speed;
	translationOffset = glm::vec3(x, y, z);
	
}

glm::mat4 RandomTranslate::getMatrix()
{
	float currentTime = glfwGetTime();
	float deltaTime = currentTime - lastUpdateTime;

	
	if (deltaTime >= speed) {
		translationOffset.x = lowerBoundX + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (upperBoundX - lowerBoundX))) + translation.x;
		translationOffset.y = lowerBoundY + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (upperBoundY - lowerBoundY))) + translation.y;
		translationOffset.z = lowerBoundZ + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (upperBoundZ - lowerBoundZ))) + translation.z;
		lastUpdateTime = currentTime;
	}
	
	return glm::translate(glm::mat4(1.0f), translationOffset);
}

void RandomTranslate::setBoundsX(float lower, float upper)
{
	lowerBoundX = lower;
	upperBoundX = upper;
}

void RandomTranslate::setBoundsY(float lower, float upper)
{
	lowerBoundY = lower;
	upperBoundY = upper;
}

void RandomTranslate::setBoundsZ(float lower, float upper)
{
	lowerBoundZ = lower;
	upperBoundZ = upper;
}


