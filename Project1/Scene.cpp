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

void Scene::removeObject(GLuint id)
{
	for(auto object : objects)
	{
		cout << "Removing object with id: " << id << objects.size() << endl;
		if(object->getId() == id )
		{
			cout << "Removing object with id: " << id << objects.size() << endl;
			objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
			return;
		}else if(id == objects.size())
		{
			DrawableObject* obj = objects.at(0);
			objects.erase(std::remove(objects.begin(), objects.end(), obj), objects.end());
			return;
		}
	}
}

void Scene::render()
{
	if (skyEnabled)
	{
		skyCubeObject->getShaderProgram()->setSkyCubeFreeze(skyBoxFreeze);
		skyCubeObject->setSkyBoxFreeze(skyBoxFreeze);
		skyCubeObject->draw();
	}
	glEnable(GL_STENCIL_TEST);
	glClear(GL_STENCIL_BUFFER_BIT);
	for (int i = 0; i < objects.size(); i++)
	{
		objects.at(i)->draw();
		objects.at(i)->setId(i);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilFunc(GL_ALWAYS, i + 1 , 0xFF);
	}
	glDisable(GL_STENCIL_TEST);
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
	light->setId(-1);
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

std::vector<Light*> Scene::getLights()
{
	return this->lights;
}

void Scene::setSkyBoxFreeze(bool freeze)
{
	skyBoxFreeze = freeze;
}



