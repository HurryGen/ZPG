#pragma once
#include <string>
#include <glm/vec3.hpp>

class Material
{
public:
    Material(glm::vec3 ra, glm::vec3 rd, glm::vec3 rs);
    Material(glm::vec3 ra, glm::vec3 rd, glm::vec3 rs, std::string texturePath);
    glm::vec3 getRa();
    glm::vec3 getRd();
    glm::vec3 getRs();
    std::string getTexturePath();
private:
    glm::vec3 ra;
    glm::vec3 rd;
    glm::vec3 rs;
    std::string texturePath;
    
};
