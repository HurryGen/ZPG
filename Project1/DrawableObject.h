#pragma once
#include "Model.h"
#include "Transformation.h"
#include "ShaderProgram.h"
class DrawableObject
{
public:
	DrawableObject(Model* model, ShaderProgram* shader);
	void setTransformation(Transformation& transformation);
	ShaderProgram* getShaderProgram();
	void draw();
private:
	Model* model;
	Transformation transformation;
	ShaderProgram* shader;
};

