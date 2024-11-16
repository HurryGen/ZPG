#include "DrawableObject.h"

DrawableObject::DrawableObject(Model* model, ShaderProgram* shader)
{
	this->model = model;
	this->shader = shader;
}

void DrawableObject::setTransformation(Transformation& transformation)
{
	this->transformation = transformation;
	shader->setTransformation(transformation);
}

ShaderProgram* DrawableObject::getShaderProgram()
{
	return shader;
}

void DrawableObject::draw()
{
	shader->use();
	shader->setTransformation(transformation);
	model->draw();
}
