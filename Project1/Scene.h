#pragma once
#include <vector>
#include "DrawableObject.h"
#include "ShaderProgram.h"
#include "SkyCube.h"

class Scene
{
public:
	Scene();
	~Scene();
	void addObject(DrawableObject* object);
	void render();
	void setCamera(Camera* camera);
	void addLight(Light* light);
	void removeLight(Light* light);
	void cameraInit();
	void lightsInit();
	void setSkyEnabled(bool enabled);
	std::vector<DrawableObject*> getObjects();
	void renderSkybox();

private:
	std::vector<DrawableObject*> objects;
	std::vector<ShaderProgram*> shaders;
	Camera* camera;
	std::vector<Light*> lights;
	bool skyEnabled = false;
	SkyCube* skyCube;
	DrawableObject* skyCubeObject;
	ShaderProgram* shaderSkybox;

};

