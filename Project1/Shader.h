#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include "Transformation.h"

#include "Observer.h"
#include "Camera.h"

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr


class Shader : public Observer
{
public:
	Shader(const char* vertex_shader,const char* fragment_shader);
	~Shader();
	void setTransformation(Transformation &transformation);
	void update(Subject* subject) override;
	void use();

private:
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
	glm::mat4 M = glm::mat4(1.0f);
	GLint idModelTransform;
	GLint idModelView;
	GLint idModelProjection;
};

#endif
