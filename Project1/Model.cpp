#include "Model.h"
#include "../Models/tree.h"



float points[] = {
	 0.0f, 0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,

	0.9f, 0.9f, 0.0f,
	 0.9f, 0.6f, 0.0f,
	0.6f, 0.6f, 0.0f,
	0.6f, 0.9f, 0.0f,

};

const float a[] = {
	 -.5f, -.5f, .5f,  0, 0, 1,
	 -.5f, .5f, .5f,  0, 0, 1,
	   .5f, .5f, .5f,  0, 0, 1,
	   .5f, -.5f, .5f,  0, 0, 1 
};

Model::Model(const float* model, size_t vertexCount, GLuint mode, int first, int count): mode(mode), first(first), count(count) {
	//vertex buffer object (VBO)
	VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), model, GL_STATIC_DRAW);

	//Vertex Array Object (VAO)
	VAO = 0;
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
}

void Model::draw()
{
	glBindVertexArray(VAO);
	glDrawArrays(mode, first, count); 
}
