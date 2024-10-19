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
}

void Scene::render()
{
	for (DrawableObject* object : objects) {
		object->draw();
	}
}

std::vector<DrawableObject*> Scene::getObjects()
{
	return objects;
}
