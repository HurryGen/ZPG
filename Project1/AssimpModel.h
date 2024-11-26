#pragma once
#include <string>

#include "AbstractModel.h"

class AssimpModel : public AbstractModel
{
public:
    AssimpModel(std::string fileName, GLuint mode);
    void draw() override;
private:
    struct Vertex
    {
        float Position[3];
        float Normal[3];
        float Texture[2];
        float Tangent[3];
    };
    GLuint VAO = 0;
    int indicesCount = 0;
    GLuint mode;
};
