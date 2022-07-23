#include "game_object.h"

GameObject::GameObject(){}

GameObject::GameObject(vec3 _position, float _size) {
	position = _position;
	size = _size;
}

void GameObject::Update(float ts) {
	if (!physC.empty()) {
		for (PhysicsComponent* pC : physC) {
			pC->Update(&position, ts);
		}
	}
}

void GameObject::Draw() {
	for (RenderComponent* rC : renderC) {
		rC->Draw(position, size);
	}
}