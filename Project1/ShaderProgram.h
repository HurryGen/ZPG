#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/glew.h>
#include <string>
#include "Transformation.h"
#include "ShaderLoader.h"
#include "Light.h"
#include "Observer.h"
#include "Camera.h"
#include <SOIL.h> 

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "Material.h"
#include "ShaderProgram.h"


class ShaderProgram : public Observer
{
	
public:
	ShaderProgram(const char* vertexFilePath, const char* fragmentFilePath);
	void setTransformation(Transformation &transformation);
	void update(Subject* subject) override;
	void setNumberOfLights(int numLights);
	void setMaterial(Material* material);
	void use();
	void use0();

private:
	GLuint shaderProgram;
	glm::mat4 M = glm::mat4(1.0f);
	GLint idModelTransform;
	GLint idModelView;
	GLint idModelProjection;
	GLint idCameraPosition;
	GLint idNumLights;
};

#endif
