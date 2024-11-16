#include "DrawableLight.h"

DrawableLight::DrawableLight(Model* model, ShaderProgram* shader, Light* light):DrawableObject(model, shader), Light(light->getPosition(), light->getColor())
{
    this->model = model;
    this->shader = shader;
    this->mode = light->getMode();
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
    shader->use();
    shader->setTransformation(transformation);
    this->position = transformation.getMatrix()[3];
    this->notify();
    cout << "Position Object: " << transformation.getMatrix()[3][0] << " " << transformation.getMatrix()[3][1] << " " << transformation.getMatrix()[3][2] << endl;
    cout <<"Position Light: " <<position.x << " " << position.y << " " << position.z << endl;
    model->draw();
}
