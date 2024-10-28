#pragma once
#include "TransformationComponent.h"

class Translate : public TransformationComponent
{
public:
private:
    glm::vec3 translation;

public:
    Translate(float x, float y, float z);
    glm::mat4 getMatrix() const override;
};

