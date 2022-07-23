#pragma once
#include "component.h"
#include "glm\vec3.hpp"

using namespace glm;

class PhysicsComponent : public Component {
	vec3 velocity = vec3(0.0f);
	vec3 acceleration = vec3(0.0f);
public:
	PhysicsComponent();
	vec3 getVelocity() {
		return vec3(velocity);
	}

	void setVelocity(vec3 newVelo);

	void setPosition(vec3 *pos, vec3 newPos);

	void setAcceleration(vec3 newAcc);

	vec3 getAcceleration() {
		return acceleration;
	}

	void Update(vec3 *pos, float ts);
};