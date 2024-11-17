#include "Material.h"

glm::vec3 Material::getRs()
{
    return rs;
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
}

glm::vec3 Material::getRa()
{
    return ra;
}
