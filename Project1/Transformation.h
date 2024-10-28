#pragma once

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <vector>
#include "TransformationComponent.h"
#include "Scale.h"
#include "Translate.h"
#include "Rotate.h"
#include <memory>
class Transformation : public TransformationComponent
{
public:
	void add(const std::shared_ptr<TransformationComponent>& transformation);
	glm::mat4 getMatrix() const override;

private:
	std::vector<std::shared_ptr<TransformationComponent>> transformations;
};

