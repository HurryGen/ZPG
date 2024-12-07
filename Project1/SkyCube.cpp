#include "SkyCube.h"

#include <iostream>
#include <SOIL.h>

SkyCube::SkyCube(): Model(skycube, 108, GL_TRIANGLES, 0)
{
    //vertex buffer object (VBO)
    VBO = 0;
    glGenBuffers(1, &VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 108 * sizeof(float), skycube, GL_STATIC_DRAW);

    //Vertex Array Object (VAO)
    VAO = 0;
    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO
    glEnableVertexAttribArray(0); //enable vertex attributes
    //glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
    glActiveTexture(GL_TEXTURE0);
    GLuint image = SOIL_load_OGL_cubemap("../Models/cubemap/posx.jpg", "../Models/cubemap/negx.jpg", "../Models/cubemap/posy.jpg", "../Models/cubemap/negy.jpg", "../Models/cubemap/posz.jpg", "../Models/cubemap/negz.jpg", SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    if (image == NULL) {
        std::cout << "An error occurred while loading CubeMap." << std::endl;
        exit(EXIT_FAILURE);
    }
    glBindTexture(GL_TEXTURE_2D, image);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}

void SkyCube::draw()
{
    if(!freeze)
    {
        glDepthMask(GL_FALSE);
    }
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 108);
    glDepthMask(GL_TRUE);
}

void SkyCube::setFreeze(bool freeze)
{
    this->freeze = freeze;
}
