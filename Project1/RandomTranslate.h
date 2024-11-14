#pragma once
#include "Translate.h"
class RandomTranslate : public Translate
{
public:
	RandomTranslate(float speed, float x, float y, float z);
	glm::mat4 getMatrix() override;
	void setBoundsX(float lower, float upper);
	void setBoundsY(float lower, float upper);
	void setBoundsZ(float lower, float upper);

private:
	float lowerBoundX;
	float upperBoundX;
	float lowerBoundY;
	float upperBoundY;
	float lowerBoundZ;
	float upperBoundZ;
	float lastUpdateTime;
	float speed;
	glm::vec3 translationOffset;
	glm::vec3 startPosition;
};

