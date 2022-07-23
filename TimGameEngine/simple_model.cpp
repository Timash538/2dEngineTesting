#include "simple_model.h"
#include "tim_utils.h"
#include <stdio.h>
#include <iostream>

SimpleModel::SimpleModel(const std::vector<vec3> &_vertices, const std::vector<unsigned int> &_indices) {

	vertices = _vertices;
	indices = _indices;
	num_elements = 6;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)*sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

SimpleModel::SimpleModel() {}

SimpleModel::SimpleModel(vec3 _vertices[], unsigned int _indices[]) {
	
	/*vec3 vertices[] = {  };*/
	/*const vec3 vertices[4] = 
	{	vec3(-1.0f, -1.0f, 0.0f),
		vec3(-1.0f, 1.0f, 0.0f),
		vec3(1.0f, 1.0f, 0.0f),
		vec3(1.0f, -1.0f, 0.0f)
	};
	const unsigned int indices[] = { 0,1,2,0,2,3 };
	num_elements = sizeof(_indices) / sizeof(*_indices);*/
	/*vertices[0] = vec3(-1.0f, -1.0f, 0.0f);
	vertices[1] = vec3(-1.0f, 1.0f, 0.0f);
	vertices[2] = vec3(1.0f, 1.0f, 0.0f);
	vertices[3] = vec3(1.0f, -1.0f, 0.0f);*/
	/*showVec(_vertices[0]);
	showVec(_vertices[1]);
	showVec(_vertices[2]);
	showVec(_vertices[3]);
	std::cout << _indices[0] << _indices[1] << _indices[2] << _indices[3] << _indices[4] << _indices[5];*/
	num_elements = 6;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

unsigned int SimpleModel::numOfElements() {
	return num_elements;
}

GLuint SimpleModel::getVAO() {
	return VAO;
}