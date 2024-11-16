#pragma once
#include "Drawable.h"
#include "Model.h"
#include "Transformation.h"
#include "ShaderProgram.h"
class DrawableObject : public Drawable
{
public:
	DrawableObject(Model* model, ShaderProgram* shader);
	void setTransformation(Transformation& transformation) override;
	ShaderProgram* getShaderProgram();
	void draw() override;

	
};

