#pragma once
#include <vector>
#include "render_component.h"
#include "glm/vec3.hpp"
#include "physics_component.h"

struct GameObject {
	
	vec3 position = vec3(0.0f);
	float size=30.0f;
	
	
	std::vector<RenderComponent*> renderC;
	std::vector<PhysicsComponent*> physC;

	GameObject();
	GameObject(vec3 pos, float siz);

	void Update(float ts);


	void Draw();
};