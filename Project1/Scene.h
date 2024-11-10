#pragma once
#include <vector>
#include "DrawableObject.h"
#include "ShaderProgram.h"
class Scene
{
public:
	Scene();
	~Scene();
	void addObject(DrawableObject* object);
	void render();
	void setCamera(Camera* camera);
	//void setLight(Light* light);
	void addLight(Light* light);
	void removeLight(Light* light);
	void cameraInit();
	void lightInit();
	std::vector<DrawableObject*> getObjects();

private:
	std::vector<DrawableObject*> objects;
	std::vector<ShaderProgram*> shaders;
	Camera* camera;
	Light* light;
	std::vector<Light*> lights;

};

