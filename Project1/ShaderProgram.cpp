#include "ShaderProgram.h"
#include <iostream>
#include <fstream>
#include <sstream>

ShaderProgram::ShaderProgram(const char* vertex_shader, const char* fragment_shader) {
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader, NULL);
    glCompileShader(vertexShader);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
    glCompileShader(fragmentShader);
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, fragmentShader);
    glAttachShader(shaderProgram, vertexShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    GLint status;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar* strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    }

   
    idModelTransform = glGetUniformLocation(shaderProgram, "modelMatrix");
    idModelView = glGetUniformLocation(shaderProgram, "viewMatrix");
    idModelProjection = glGetUniformLocation(shaderProgram, "projectionMatrix");

}

void ShaderProgram::setTransformation(Transformation& transformation)
{
    M = transformation.getMatrix();

    glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &M[0][0]);
}

void ShaderProgram::update(Subject* subject)
{
    if (auto camera = dynamic_cast<Camera*>(subject)) {
        glUniformMatrix4fv(idModelView, 1, GL_FALSE, glm::value_ptr(camera->getCamera()));
        glUniformMatrix4fv(idModelProjection, 1, GL_FALSE, glm::value_ptr(camera->getProjection()));
    }
}

void ShaderProgram::use()
{
    glUseProgram(shaderProgram);
}

