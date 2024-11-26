#pragma once
#include <string>

#include "AbstractModel.h"

class AssimpModel : public AbstractModel
{
public:
    AssimpModel(std::string path);
    void draw() override;
};
