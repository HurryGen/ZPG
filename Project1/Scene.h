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
	std::vector<DrawableObject*> getObjects();

private:
	std::vector<DrawableObject*> objects;

};

