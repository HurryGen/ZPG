#include "Material.h"

#include <iostream>
#include <SOIL.h>

glm::vec3 Material::getRs()
{
    return rs;
}


GLuint Material::getTextureUnit()
{
    return textureUnit;
}

glm::vec3 Material::getRd()
{
    return rd;
}

Material::Material(glm::vec3 ra, glm::vec3 rd, glm::vec3 rs)
{
    this->ra = ra;
    this->rd = rd;
    this->rs = rs;
    this->texturePath = "";
}

Material::Material(glm::vec3 ra, glm::vec3 rd, glm::vec3 rs, std::string texturePath, GLuint textureUnit)
{
    this->ra = ra;
    this->rd = rd;
    this->rs = rs;
   
    this->textureUnit = textureUnit;
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    GLuint textureID = SOIL_load_OGL_texture(texturePath.c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if(!textureID)
    {
        std::cerr << "Error loading texture: " << texturePath << std::endl;
    }
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

glm::vec3 Material::getRa()
{
    return ra;
}
