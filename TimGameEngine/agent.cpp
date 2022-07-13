#include "agent.h"
#include "tim_utils.h"

void Agent::Draw(Shader shader, vec2 resolution,vec2 scene, vec2 cam) {
	shader.use();
	shader.setVec3("Pos", position);
	shader.setVec3("bColor", vec3(0.3f, 0.3f, 1.0f));
	shader.setFloat("Size", size);
	shader.setVec3("scene", vec3(scene.x,scene.y,0.0f));
	shader.setVec3("res", vec3(resolution.x,resolution.y,0.0f));
	shader.setVec3("cam", vec3(cam.x,cam.y,0.0f));
	shader.setVec3("Color", vec3(sqrt(pow(velocity.x,2)/100.0f + pow(velocity.y, 2)/100.0f),vec2(0.0f)));
	shader.setVec3("SelfColor", color);
	//std::cout << velocity.x << std::endl;
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

Agent::Agent(glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration, float size) {
	color = vec3(RandomFloat(0.0f,1.0f), RandomFloat(0.0f, 1.0f), RandomFloat(0.0f, 1.0f));
	this->position = position;
	this->velocity = velocity;
	this->acceleration = acceleration;
	this->size = size;
	vertices[0] = vec3(-1.0f, -1.0f, 0.0f);
	vertices[1] = vec3(-1.0f, 1.0f, 0.0f);
	vertices[2] = vec3(1.0f, 1.0f, 0.0f);
	vertices[3] = vec3(1.0f, -1.0f, 0.0f);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void Agent::Update(float timeStamp) {
	setVelocity(velocity + acceleration*timeStamp);
	setPosition(position + velocity*timeStamp+acceleration*timeStamp*timeStamp/2.0f);
}

void Agent::setAcceleration(vec3 newAcc) {
	acceleration = newAcc;
}

void Agent::setAcceleration(vec3 newAcc, float timeStamp) {
	acceleration = newAcc * timeStamp;
}

void Agent::setPosition(vec3 newPos, float timeStamp) {
	position = newPos * timeStamp;
}

void Agent::setPosition(vec3 newPos) {
	position = newPos;
}


void Agent::setVelocity(vec3 newVelo) {
	velocity = newVelo;
}

void Agent::setVelocity(vec3 newVelo, float timeStamp) {
	velocity = newVelo * timeStamp;
}


void Agent::setSize(float nSize) {
	size = nSize;
}

float Agent::getSize() {
	return size;
}