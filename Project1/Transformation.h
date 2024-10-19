#pragma once
//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

class Transformation
{
public:
	Transformation();
	void translate(float x, float y, float z);
	void rotate(float angle, float x, float y, float z);
	void scale(float x, float y, float z);
	void reset();
	glm::mat4 getMatrix();

private:
	glm::mat4 translationMat;
	glm::mat4 rotationMat;
	glm::mat4 scaleMat;
};

