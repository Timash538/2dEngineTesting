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
	glm::vec3 velocity = vec3(0.0f,0.0f,0.0f);
	glm::vec3 acceleration;
	glm::vec3 vertices[1];
	int num_vertices;
	GLuint VAO;
	GLuint VBO;
public:
	Agent(glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration);

	Agent() {}

	vec3 getVelocity() {
		return vec3(velocity);
	}
	
	void setVelocity(vec3 newVelo) {
		velocity = newVelo;
	}

	vec3 getPosition() {
		return position;
	}

	void setPosition(vec3 newPos) {
		position = newPos;
	}

	void setAcceleration(vec3 newAcc);

	vec3 getAcceleration() {
		return acceleration;
	}

	void Update();

	void Draw(Shader shader, vec2 res, vec2 scene, vec2 cam);

};