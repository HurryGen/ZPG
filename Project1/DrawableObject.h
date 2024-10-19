#pragma once
#include "Model.h"
#include "Transformation.h"
#include "Shader.h"
class DrawableObject
{
public:
	DrawableObject(Model* model, Shader* shader);
	void setTransformation(Transformation& transformation);
	void draw();
private:
	Model* model;
	Transformation transformation;
	Shader* shader;
};

