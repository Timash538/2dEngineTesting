#pragma once
#include "agent.h"
#include <vector>

using namespace std;

struct Scene {
	vector<Agent> agents;
	vec2 space;
	vec2 resolution;
	vec3 mousePos = vec3(0.0f);
};