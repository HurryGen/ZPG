#pragma once
#include "Transformation.h"
class Observer
{
public:
	virtual void setTransformation(Transformation& transformation) = 0;
	virtual void use() = 0;
};

