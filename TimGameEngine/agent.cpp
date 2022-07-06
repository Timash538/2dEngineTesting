#include "agent.h"
#include "tim_utils.h"

void Agent::Draw(Shader shader, vec2 resolution,vec2 scene, vec2 cam) {
	shader.use();
	shader.setVec3("Pos", position);
	shader.setVec3("scene", vec3(scene.x,scene.y,0.0f));
	shader.setVec3("res", vec3(resolution.x,resolution.y,0.0f));
	shader.setVec3("cam", vec3(cam.x,cam.y,0.0f));
	shader.setVec3("Color", vec3(sqrt(pow(velocity.x,2)/100.0f + pow(velocity.y, 2)/100.0f),vec2(0.0f)));
	shader.setVec3("SelfColor", color);
	//std::cout << velocity.x << std::endl;
	glBindVertexArray(VAO);
	glDrawArrays(GL_POINTS, 0, 1);
	glBindVertexArray(0);
}

Agent::Agent(glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration) {
	color = vec3(0.5f);//vec3(RandomFloat(0.0f,1.0f), RandomFloat(0.0f, 1.0f), RandomFloat(0.0f, 1.0f));
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

void Agent::Update() {
	setVelocity(velocity + acceleration);
	setPosition(position + velocity);
}

void Agent::setAcceleration(vec3 newAcc) {
	acceleration = vec3(newAcc.x/100.0f, newAcc.y/100.0f, 0.0f);
}