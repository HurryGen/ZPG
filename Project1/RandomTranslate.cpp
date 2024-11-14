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
	startPosition = glm::vec3(x, y, z);
	
}

glm::mat4 RandomTranslate::getMatrix()
{
	float currentTime = glfwGetTime();
	float deltaTime = currentTime - lastUpdateTime;

	
	if (deltaTime >= speed) {
		translation = translationOffset;
		translationOffset.x = lowerBoundX + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (upperBoundX - lowerBoundX))) + startPosition.x;
		translationOffset.y = lowerBoundY + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (upperBoundY - lowerBoundY))) + startPosition.y;
		translationOffset.z = lowerBoundZ + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (upperBoundZ - lowerBoundZ)))+ startPosition.z;
		lastUpdateTime = currentTime;
		deltaTime = 0.0f;
	}
	float alpha = glm::clamp(deltaTime / speed, 0.0f, 1.0f);
	glm::vec3 interpolatedOffset = glm::mix(translation, translationOffset, alpha);
	
	return glm::translate(glm::mat4(1.0f), interpolatedOffset);
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


