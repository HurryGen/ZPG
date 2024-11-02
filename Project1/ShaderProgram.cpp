#include "ShaderProgram.h"
#include <iostream>
#include <fstream>
#include <sstream>

ShaderProgram::ShaderProgram(const char* vertexFilePath, const char* fragmentFilePath) {
    
    ShaderLoader shaderLoader;
    shaderProgram = shaderLoader.loadShader(vertexFilePath, fragmentFilePath);

    
    if (shaderProgram == 0) {
        std::cerr << "Failed to create shader program." << std::endl;
        return;
    }

    
    idModelTransform = glGetUniformLocation(shaderProgram, "modelMatrix");
    idModelView = glGetUniformLocation(shaderProgram, "viewMatrix");
    idModelProjection = glGetUniformLocation(shaderProgram, "projectionMatrix");
    idLightColor = glGetUniformLocation(shaderProgram, "lightColor");
    idLightPosition = glGetUniformLocation(shaderProgram, "lightPosition");

}

void ShaderProgram::setTransformation(Transformation& transformation)
{
    M = transformation.getMatrix();

    glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &M[0][0]);
}

void ShaderProgram::update(Subject* subject)
{
    if (auto camera = dynamic_cast<Camera*>(subject)) {
        use();
        glUniformMatrix4fv(idModelView, 1, GL_FALSE, glm::value_ptr(camera->getCamera()));
        glUniformMatrix4fv(idModelProjection, 1, GL_FALSE, glm::value_ptr(camera->getProjection()));
    }

    if (auto light = dynamic_cast<Light*>(subject)) {
        use();
        glUniform3fv(idLightPosition, 1, glm::value_ptr(light->getPosition()));
        glUniform4fv(idLightColor, 1, glm::value_ptr(light->getColor()));
    }
}

void ShaderProgram::use()
{
    glUseProgram(shaderProgram);
}

