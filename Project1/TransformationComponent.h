#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
class TransformationComponent
{
public:
	virtual glm::mat4 getMatrix() = 0;
};

