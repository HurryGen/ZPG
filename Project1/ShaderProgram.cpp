#include "ShaderProgram.h"
#include <iostream>
#include <fstream>
#include <sstream>

ShaderProgram::ShaderProgram(const char* vertexFilePath, const char* fragmentFilePath)
{
    ShaderLoader shaderLoader;
    shaderProgram = shaderLoader.loadShader(vertexFilePath, fragmentFilePath);


    if (shaderProgram == 0)
    {
        std::cerr << "Failed to create shader program." << std::endl;
        return;
    }


    idModelTransform = glGetUniformLocation(shaderProgram, "modelMatrix");
    idModelView = glGetUniformLocation(shaderProgram, "viewMatrix");
    idModelProjection = glGetUniformLocation(shaderProgram, "projectionMatrix");
    idCameraPosition = glGetUniformLocation(shaderProgram, "cameraPosition");
    //idLightColor = glGetUniformLocation(shaderProgram, "lightColor");
    //idLightPosition = glGetUniformLocation(shaderProgram, "lightPosition");
    idNumLights = glGetUniformLocation(shaderProgram, "numLights");
}

void ShaderProgram::setTransformation(Transformation& transformation)
{
    M = transformation.getMatrix();

    glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &M[0][0]);
}

void ShaderProgram::update(Subject* subject)
{
    use();
    if (auto camera = dynamic_cast<Camera*>(subject))
    {
        glUniformMatrix4fv(idModelView, 1, GL_FALSE, glm::value_ptr(camera->getCamera()));
        glUniformMatrix4fv(idModelProjection, 1, GL_FALSE, glm::value_ptr(camera->getProjection()));
        glUniform3fv(idCameraPosition, 1, glm::value_ptr(camera->getPosition()));
    }

    if (auto light = dynamic_cast<Light*>(subject))
    {
        loadLights();
    }
}

void ShaderProgram::addLights(std::vector<Light*> lights)
{
    this->lights = lights;
}

void ShaderProgram::loadLights()
{
    use();
    glUniform1i(idNumLights, lights.size());
    for (int i = 0; i < lights.size(); i++)
    {
        
        glUniform3fv(glGetUniformLocation(shaderProgram, ("lights[" + std::to_string(i) + "].position").c_str()), 1, glm::value_ptr(lights[i]->getPosition()));
        glUniform4fv(glGetUniformLocation(shaderProgram, ("lights[" + std::to_string(i) + "].color").c_str()), 1, glm::value_ptr(lights[i]->getColor()));
        glUniform1i(glGetUniformLocation(shaderProgram, ("lights[" + std::to_string(i) + "].mode").c_str()), lights[i]->getMode());
        glUniform3fv(glGetUniformLocation(shaderProgram, ("lights[" + std::to_string(i) + "].spotDir").c_str()), 1, glm::value_ptr(lights[i]->getLightDirection()));
        glUniform1f(glGetUniformLocation(shaderProgram, ("lights[" + std::to_string(i) + "].cutoff").c_str()), lights[i]->getCutoff());
    }
}

void ShaderProgram::use()
{
    glUseProgram(shaderProgram);
}
