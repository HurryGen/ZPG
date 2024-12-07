#pragma once
#include "Drawable.h"
#include "Material.h"
#include "Model.h"
#include "Transformation.h"
#include "ShaderProgram.h"
class DrawableObject : public Drawable
{
public:
	DrawableObject(AbstractModel* model, ShaderProgram* shader,Material* material);
	DrawableObject(AbstractModel* model, ShaderProgram* shader);
	void setTransformation(Transformation& transformation) override;
	ShaderProgram* getShaderProgram();
	void draw() override;
	void setSkyBoxFreeze(bool freeze);
protected:
	AbstractModel* model;
	Transformation transformation;
	ShaderProgram* shader;
	Material* material;
	bool skyBoxFreeze;
	
};

