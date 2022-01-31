#pragma once
#include "glew.h"
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "shader.h"
#include "texture.h"

#include <vector>

using namespace std;
using namespace glm;

struct Vertex {
	vec3 Position;
	vec3 Normal;
	vec2 TexCoords;
};

class Mesh {
public:

	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	void Draw(Shader& shader);

private:
	GLuint VBO, VAO, IBO;

	void setupMesh();
};