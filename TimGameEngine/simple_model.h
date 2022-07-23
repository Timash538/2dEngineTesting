#pragma once

#include "glew.h"
#include "freeglut.h"
#include <vector>
#include "glm/vec3.hpp"

using namespace glm;

class SimpleModel {

private:
	GLuint VAO, VBO, IBO;
	std::vector<vec3> vertices;
	std::vector<unsigned int> indices;
	unsigned int num_elements;

public:

	SimpleModel(const std::vector<vec3>& _vertices, const std::vector<unsigned int>& _indices);
	SimpleModel(vec3 _vertices[], unsigned int _indices[]);
	SimpleModel();
	unsigned int* getIndices() {
		return &indices[0];
	}
	GLuint getVAO();
	unsigned int numOfElements();
};