#pragma once
#include "TransformationComponent.h"
class Scale : public TransformationComponent
{
private:
    glm::vec3 scaling;

public:
    Scale(float x, float y, float z);
    glm::mat4 getMatrix() const override;
};

