#pragma once
#include "agent.h"
#include <vector>

using namespace std;

struct Scene {
	vector<Agent> agents;
	vec2 space;
	vec2 resolution;
	vec2 mousePos = vec2(0.0f);
};