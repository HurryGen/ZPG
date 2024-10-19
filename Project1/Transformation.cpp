#include "Transformation.h"

Transformation::Transformation(): scaleMat(1.0f), rotationMat(1.0f), translationMat(1.0f){}

void Transformation::translate(float x, float y, float z)
{
	translationMat = glm::translate(translationMat, glm::vec3(x, y, z));
}

void Transformation::rotate(float angle, float x, float y, float z)
{
	rotationMat = glm::rotate(rotationMat,glm::radians(angle), glm::vec3(x, y, z));
}

void Transformation::scale(float x, float y, float z)
{
	scaleMat = glm::scale(scaleMat, glm::vec3(x, y, z));
}

void Transformation::reset()
{
	scaleMat = glm::mat4(1.f);
	rotationMat = glm::mat4(1.f);
	translationMat = glm::mat4(1.f);
}

glm::mat4 Transformation::getMatrix()
{
	return translationMat*rotationMat*scaleMat;
}
