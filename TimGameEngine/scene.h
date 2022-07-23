#pragma once
#include <vector>
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

using namespace std;
using namespace glm;

struct Scene {
	vec3 space;
	vec3 resolution;
	vec3 mousePos = vec3(0.0f);
	float aspectRatio;
	vec3 cam;
};