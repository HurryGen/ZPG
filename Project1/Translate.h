#pragma once
#include "TransformationComponent.h"

class Translate : public TransformationComponent
{

protected:
    glm::vec3 translation;

public:
    Translate(float x, float y, float z);
    glm::mat4 getMatrix() override;
};

