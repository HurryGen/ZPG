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

void Scene::setLight(Light* light)
{
	this->light = light;
}

void Scene::cameraInit()
{
	for (ShaderProgram* shader : shaders) {
		camera->attach(shader);
	}
	camera->notify();
}

void Scene::lightInit()
{
	for (ShaderProgram* shader : shaders) {
		light->attach(shader);
	}
	light->notify();
}



std::vector<DrawableObject*> Scene::getObjects()
{
	return objects;
}
