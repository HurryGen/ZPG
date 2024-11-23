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
	
	glActiveTexture(GL_TEXTURE + material->getTextureUnit());
	glBindTexture(GL_TEXTURE_2D, material->getTextureID());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	shader->setTransformation(transformation);
	shader->setMaterial(material);
	shader->setTexture(material->getTextureUnit());
	shader->use();
	model->draw();
	shader->use0();
}
