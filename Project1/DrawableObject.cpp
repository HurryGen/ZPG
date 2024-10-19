#include "DrawableObject.h"

DrawableObject::DrawableObject(Model* model, Shader* shader):model(model), shader(shader){}

void DrawableObject::setTransformation(Transformation& transformation)
{
	this->transformation = transformation;
	shader->setTransformation(transformation);
}

void DrawableObject::draw()
{
	shader->use();
	shader->setTransformation(transformation);
	model->draw();
}
