#pragma once
#include <glm/vec3.hpp>

class Material
{
public:
    Material(glm::vec3 ra, glm::vec3 rd, glm::vec3 rs);
    glm::vec3 getRa();
    glm::vec3 getRd();
    glm::vec3 getRs();
private:
    glm::vec3 ra;
    glm::vec3 rd;
    glm::vec3 rs;
    
};
