#include "ModelFactory.h"

#include "AssimpModel.h"
#include "Model.h"
#include "TextureModel.h"


AbstractModel* ModelFactory::createModel(ModelType type, const float* model, size_t vertexCount, GLuint mode)
{
    switch (type) {
    case ModelType::BASIC:
        return createBasicModel(model, vertexCount, mode, 0);
    case ModelType::TEXTURE:
        return createTextureModel(model, vertexCount, mode, 0);
    default:
        return nullptr;
    }
}

AbstractModel* ModelFactory::createModel(std::string fileName, GLuint mode)
{
    return createAssimpModel(fileName, mode);
}

AbstractModel* ModelFactory::createBasicModel(const float* model, size_t vertexCount, GLuint mode, int first)
{
    return new Model(model, vertexCount, mode, first);
}

AbstractModel* ModelFactory::createTextureModel(const float* model, size_t vertexCount, GLuint mode, int first)
{
    return new TextureModel(model, vertexCount, mode, first);
}

AbstractModel* ModelFactory::createAssimpModel(std::string fileName, GLuint mode)
{
    return new AssimpModel(fileName, mode);
}



