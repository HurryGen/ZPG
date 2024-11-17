#include "DrawableObject.h"

DrawableObject::DrawableObject(Model* model, ShaderProgram* shader, Material* material)
{
	this->model = model;
	this->shader = shader;
	this->material = material;
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
	shader->setMaterial(material);
	model->draw();
}
