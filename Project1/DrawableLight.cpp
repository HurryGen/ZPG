#include "DrawableLight.h"

DrawableLight::DrawableLight(Model* model, ShaderProgram* shader, Material* material, Light* light):DrawableObject(model, shader, material), Light(light->getPosition(), light->getColor(), light->getAttenuation())
{
}

void DrawableLight::setTransformation(Transformation& transformation)
{
    this->transformation = transformation;
    this->position = transformation.getMatrix()[3];
    this->notify();
    shader->setTransformation(transformation);
}



void DrawableLight::draw()
{
    shader->setTransformation(transformation);
    this->position = transformation.getMatrix()[3];
    this->notify();
    shader->setMaterial(material);
    shader->use();
    model->draw();
    shader->use0();
}
