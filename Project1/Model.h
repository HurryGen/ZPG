#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>

#include "AbstractModel.h"

class Model : public AbstractModel {
public:
	Model(const float* model, size_t vertexCount, GLuint mode, int first);
	void draw() override;

protected:
	int first;
	int count;
	size_t vertexCount;
	GLuint VBO;
	GLuint VAO;
	GLuint mode;

};

#endif
