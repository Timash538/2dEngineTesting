#pragma once

#include "glm/vec2.hpp"

#include "glew.h"
#include "glut.h"
#include "shader.h"
#include <iostream>

class Agent {
private:
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 velocity = vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 acceleration;
	glm::vec3 vertices[4];
	float size;
	int num_vertices;
	unsigned int indices[6] ={0,1,2,0,2,3};
	GLuint VAO;
	GLuint VBO;
	GLuint IBO;
public:
	Agent(glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration, float size);

	Agent() {}

	vec3 getVelocity() {
		return vec3(velocity);
	}
	
	void setVelocity(vec3 newVelo, float ts);
	void setVelocity(vec3 newVelo);

	vec3 getPosition() {
		return position;
	}

	void setPosition(vec3 newPos, float ts);
	void setPosition(vec3 newPos);

	float getSize();

	void setSize(float nSize);

	void setAcceleration(vec3 newAcc);
	void setAcceleration(vec3 newAcc,float ts);

	vec3 getAcceleration() {
		return acceleration;
	}

	void Update();

	void Update(float ts);

	void Draw(Shader shader, vec2 res, vec2 scene, vec2 cam);

};