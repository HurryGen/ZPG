#include "DrawableObject.h"

#include "SkyCube.h"

DrawableObject::DrawableObject(AbstractModel* model, ShaderProgram* shader, Material* material)
{
	this->model = model;
	this->shader = shader;
	this->material = material;
}

DrawableObject::DrawableObject(AbstractModel* model, ShaderProgram* shader)
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
	shader->setTransformation(transformation);
	shader->setMaterial(material);
	shader->setTexture(material->getTextureUnit());
	shader->use();
	model->draw();
	shader->use0();
}

void DrawableObject::setSkyBoxFreeze(bool freeze)
{
	if(auto skyCube = dynamic_cast<SkyCube*>(model))
	{
		skyCube->setFreeze(freeze);
	}
	
}

int DrawableObject::getId()
{
	return id;
}

void DrawableObject::setId(int id)
{
	this->id = id;
}
