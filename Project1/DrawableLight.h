#pragma once
#include "Drawable.h"
#include "DrawableObject.h"

class DrawableLight: public DrawableObject, public Light
{
public:
    DrawableLight(AbstractModel* model, ShaderProgram* shader,Material* material, Light* light);
    void setTransformation(Transformation& transformation) override;
    void draw() override;
};
