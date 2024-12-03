#pragma once
#include <string>
#include <GL/glew.h>
#include "AbstractModel.h"

enum class ModelType {
    BASIC,   
    TEXTURE
};



class ModelFactory
{
    
public:
    
    static AbstractModel* createModel(ModelType type, const float* model, size_t vertexCount, GLuint mode);
    static AbstractModel* createModel(std::string fileName, GLuint mode);
private:
    static AbstractModel* createBasicModel(const float* model, size_t vertexCount, GLuint mode, int first);
    static AbstractModel* createTextureModel(const float* model, size_t vertexCount, GLuint mode, int first);
    static AbstractModel* createAssimpModel(std::string fileName, GLuint mode);
    
    
};
