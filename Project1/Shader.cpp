#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>


Shader::Shader(const char* vertex_shader, const char* fragment_shader) {
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

   

    GLint idModelTransform = glGetUniformLocation(shaderProgram, "modelMatrix");
    GLint idModelView = glGetUniformLocation(shaderProgram, "viewMatrix");
    GLint idModelProjection = glGetUniformLocation(shaderProgram, "projectionMatrix");
   

    glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &M[0][0]);
    glUniformMatrix4fv(idModelView, 1, GL_FALSE, &M[0][0]);
    glUniformMatrix4fv(idModelProjection, 1, GL_FALSE, &M[0][0]);

   


}

void Shader::setTransformation(Transformation& transformation)
{
    M = transformation.getMatrix();
    GLint idModelTransform = glGetUniformLocation(shaderProgram, "modelMatrix");
    GLint idModelView = glGetUniformLocation(shaderProgram, "viewMatrix");
    GLint idModelProjection = glGetUniformLocation(shaderProgram, "projectionMatrix");

    glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &M[0][0]);
   
}

void Shader::use()
{
    glUseProgram(shaderProgram);
}

