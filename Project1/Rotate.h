#pragma once
#include "TransformationComponent.h"
class Rotate : public TransformationComponent
{
protected:
	float angle;
	glm::vec3 axis;

public:
	Rotate(float angle, float x, float y, float z);
	glm::mat4 getMatrix() override;
};

