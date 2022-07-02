#pragma once

#include "glm/vec2.hpp"
#include "glut.h"
#include "glew.h"
#include "shader.h"

class Agent {
private:
	glm::vec3 position;
	glm::vec3 velocity = vec3(0.0f,0.0f,0.0f);
	glm::vec3 acceleration;
	glm::vec3 vertices[1];
	int num_vertices;
	GLuint VAO;
	GLuint VBO;
public:
	Agent(glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration) {

		this->position = position;
		vertices[0] = vec3(0.0f, 0.0f, 0.0f);
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

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

	void setAcceleration(vec3 newAcc) {
		acceleration = vec3(newAcc.x/1000.0f,newAcc.y/1000.0f,0.0f);
	}

	void Update() {
		setVelocity(velocity + acceleration);
		setPosition(position + velocity);
	}

	void Draw(Shader shader) {
		
		shader.use();
		shader.setVec3("Pos", position);
		glBindVertexArray(VAO);
		glDrawArrays(GL_POINTS, 0, 1);
		glBindVertexArray(0);
	}
};