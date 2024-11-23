#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>

class Model {
public:
	Model(const float* model, size_t vertexCount, GLuint mode, int first, int count);
	virtual void draw();

protected:
	GLuint VBO;
	GLuint VAO;
	GLuint mode;
	int first;
	int count;

};

#endif
