#pragma once
#include "Model.h"
#include "Transformation.h"
#include "ShaderProgram.h"

class Drawable
{
public:
    virtual void setTransformation(Transformation& transformation) = 0;
    virtual void draw() = 0;

protected:
    Model* model;
    Transformation transformation;
    ShaderProgram* shader;
    
    
};
