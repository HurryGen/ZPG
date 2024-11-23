#include "DrawableObject.h"

#include "SkyCube.h"

DrawableObject::DrawableObject(Model* model, ShaderProgram* shader, Material* material)
{
	this->model = model;
	this->shader = shader;
	this->material = material;
}

DrawableObject::DrawableObject(Model* model, ShaderProgram* shader)
{	
	this->model = model;
	this->shader = shader;
	this->material = new Material(glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f));
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
