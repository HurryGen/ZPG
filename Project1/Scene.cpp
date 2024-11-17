#include "Scene.h"

Scene::Scene()
{

}

Scene::~Scene()
{
	for (DrawableObject* object : objects) {
		delete object;
	}
}

void Scene::addObject(DrawableObject* object)
{
	objects.push_back(object);
	shaders.push_back(object->getShaderProgram());
}

void Scene::render()
{
	for (DrawableObject* object : objects) {
		object->draw();
	}
	
}

void Scene::setCamera(Camera* camera)
{
	this->camera = camera;
}

void Scene::addLight(Light* light)
{
	lights.push_back(light);
}

void Scene::removeLight(Light* light)
{
	lights.erase(std::remove(lights.begin(), lights.end(), light), lights.end());
}

void Scene::cameraInit()
{
	for (ShaderProgram* shader : shaders) {
		camera->attach(shader);
	}
	camera->notify();
}

void Scene::lightsInit()
{
	for (ShaderProgram* shader : shaders) {
		shader->setNumberOfLights(lights.size());
	}
	for(int i = 0; i < lights.size(); i++)
	{
		lights[i]->setId(i);
		lights[i]->notify();
	}
	
}



std::vector<DrawableObject*> Scene::getObjects()
{
	return objects;
}
