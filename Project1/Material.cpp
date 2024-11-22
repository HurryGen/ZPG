#include "Material.h"

#include <SOIL.h>

glm::vec3 Material::getRs()
{
    return rs;
}


GLuint Material::getTextureUnit()
{
    return textureUnit;
}

GLuint Material::getTextureID()
{
    return textureID;
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
    this->textureID = SOIL_load_OGL_texture(texturePath.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    this->textureUnit = textureUnit;
}

glm::vec3 Material::getRa()
{
    return ra;
}
