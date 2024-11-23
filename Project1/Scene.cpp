#include "Scene.h"

#include "SkyCube.h"

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
	if (skyEnabled)
	{
		skyCubeObject->draw();
		
	}
	for (DrawableObject* object : objects)
	{
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

void Scene::setSkyEnabled(bool enabled)
{
	skyCube = new SkyCube();
	shaderSkybox = new ShaderProgram("vertex_shader_skybox.glsl", "fragment_shader_skybox.glsl");
	skyCubeObject = new DrawableObject(skyCube, shaderSkybox);
	shaders.push_back(shaderSkybox);
	skyEnabled = enabled;
}


std::vector<DrawableObject*> Scene::getObjects()
{
	return objects;
}

void Scene::renderSkybox()
{
	if (skyEnabled) {
		skyCubeObject->draw();
	}
}
