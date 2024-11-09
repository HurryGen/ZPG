#pragma once
#include "Rotate.h"
#include <GLFW/glfw3.h>
class DynamicRotate : public Rotate
{
public:
	DynamicRotate(float speed,float x, float y, float z);
	glm::mat4 getMatrix() override;
private:
	float speed;
	float lastUpdateTime;

};

