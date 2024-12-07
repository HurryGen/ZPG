#include "SceneController.h"

SceneController::SceneController()
{
    currentSceneIndex = 0;
}

void SceneController::addScene(Scene* scene)
{
    scenes.push_back(scene);
}

void SceneController::removeScene(Scene* scene)
{
    scenes.erase(std::remove(scenes.begin(), scenes.end(), scene), scenes.end());
}

void SceneController::render()
{
    scenes[currentSceneIndex]->render();
}

void SceneController::setCamera(Camera* camera)
{
    SceneController::camera = camera;
}

void SceneController::switchScene(int index)
{
    for (int i = 0; i < scenes.size(); i++)
    {
        for(Light* light : scenes[i]->getLights())
        {
            light->setId(-1);
        }
    }
    currentSceneIndex = index;
    scenes[currentSceneIndex]->lightsInit();
}

void SceneController::freezSkyBox()
{
    skyBoxFreeze = !skyBoxFreeze;
    scenes[currentSceneIndex]->setSkyBoxFreeze(skyBoxFreeze);
}

void SceneController::spawnObject(DrawableObject* object, glm::vec3 position)
{
    Transformation transformation;
    transformation.add(std::shared_ptr<Translate>(new Translate(position.x, position.y, position.z)));
    scenes[currentSceneIndex]->addObject(object);
    object->setTransformation(transformation);
}

void SceneController::removeObject(GLuint id)
{
    scenes[currentSceneIndex]->removeObject(id);
}



