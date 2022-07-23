#pragma once
#include <string>
#include <cmath>
#include <iostream>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

using namespace glm;
using namespace std;

#define toRadian(x) x*3.1415926/180.0f

bool ReadFile(const char* FileName, std::string& outFile);

float RandomFloat(float min, float max);

float getMagnitude(vec2& start, vec2& end);

void showVec(vec3 v);