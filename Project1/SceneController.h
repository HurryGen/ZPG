#pragma once


#include "Scene.h"

class SceneController
{
public:
    SceneController();
    void addScene(Scene* scene);
    void removeScene(Scene* scene);
    void render();
    void setCamera(Camera* camera);
    void switchScene(int index);
    void freezSkyBox();
    void spawnObject(DrawableObject* object, glm::vec3 position);
    void removeObject(GLuint id);



private:
    std::vector<Scene*> scenes;
    Camera* camera;
    int currentSceneIndex;
    bool skyBoxFreeze = false;
    
    
    
    
};
