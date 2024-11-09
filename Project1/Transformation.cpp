#include "Transformation.h"

void Transformation::add(const std::shared_ptr<TransformationComponent>& transformation)
{
    transformations.push_back(transformation);
}

glm::mat4 Transformation::getMatrix()
{
    glm::mat4 result = glm::mat4(1.0f);
    for (const auto& transformation : transformations) {
        result *= transformation->getMatrix();
    }
    return result;
}
