#pragma once
#include <GL/glew.h>

class AbstractModel
{
public:
    virtual void draw() = 0;
    virtual ~AbstractModel() = default;
    
};
