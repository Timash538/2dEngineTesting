#include "physics_component.h"

PhysicsComponent::PhysicsComponent() {

}

void PhysicsComponent::setPosition(vec3 *pos, vec3 newPos) {
	*pos = newPos;
}

void PhysicsComponent::setVelocity(vec3 newVelo) {
	velocity = newVelo;
}

void PhysicsComponent::setAcceleration(vec3 newAcc) {
	acceleration = newAcc;
}

void PhysicsComponent::Update(vec3 *pos, float timeStamp) {
	setVelocity(velocity + acceleration * timeStamp);
	setPosition(pos,*pos + velocity * timeStamp + acceleration * timeStamp * timeStamp / 2.0f);
}