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



private:
    std::vector<Scene*> scenes;
    Camera* camera;
    int currentSceneIndex;
    bool skyBoxFreeze = false;
    
    
    
    
};
