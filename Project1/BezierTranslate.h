#pragma once


#include "TransformationComponent.h"


class BezierTranslate : public TransformationComponent
{
public:
    BezierTranslate(float delta, float t, glm::mat4 A, glm::mat4x3 B);
    glm::mat4 getMatrix() override;

private:
    glm::mat4 A;
    glm::mat4x3 B;
    float delta;
    float t;
    
};
