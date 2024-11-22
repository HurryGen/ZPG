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
    use();
    M = transformation.getMatrix();

    glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &M[0][0]);
    use0();
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
        glUniform3fv(glGetUniformLocation(shaderProgram, ("lights[" + std::to_string(light->getId()) + "].position").c_str()), 1, glm::value_ptr(light->getPosition()));
        glUniform4fv(glGetUniformLocation(shaderProgram, ("lights[" + std::to_string(light->getId()) + "].color").c_str()), 1, glm::value_ptr(light->getColor()));
        glUniform1i(glGetUniformLocation(shaderProgram, ("lights[" + std::to_string(light->getId()) + "].mode").c_str()), light->getMode());
        glUniform3fv(glGetUniformLocation(shaderProgram, ("lights[" + std::to_string(light->getId()) + "].spotDir").c_str()), 1, glm::value_ptr(light->getLightDirection()));
        glUniform1f(glGetUniformLocation(shaderProgram, ("lights[" + std::to_string(light->getId()) + "].cutoff").c_str()), light->getCutoff());
    }
    use0();
}

void ShaderProgram::setNumberOfLights(int numLights)
{
    use();
    glUniform1i(idNumLights, numLights);
    use0();
}

void ShaderProgram::setMaterial(Material* material)
{
    use();
    glUniform3fv(glGetUniformLocation(shaderProgram,"material.ra"), 1,glm::value_ptr(material->getRa()));
    glUniform3fv(glGetUniformLocation(shaderProgram,"material.rd"), 1,glm::value_ptr(material->getRd()));
    glUniform3fv(glGetUniformLocation(shaderProgram,"material.rs"), 1,value_ptr(material->getRs()));
    use0();
}

void ShaderProgram::setTexture(GLuint textureUnit)
{
    use();
    glUniform1i(glGetUniformLocation(shaderProgram, "textureUnitID"), textureUnit);
    use0();
}


void ShaderProgram::use()
{
    glUseProgram(shaderProgram);
}

void ShaderProgram::use0()
{
    glUseProgram(0);
}
