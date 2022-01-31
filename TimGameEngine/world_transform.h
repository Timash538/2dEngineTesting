#pragma once
#include "glm/vec4.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

using namespace glm;

struct WorldTransform {

	WorldTransform() {
		pos = glm::vec3(0.0f, 0.0f, 0.0f);
		rot = glm::vec3(0.0f, 0.0f, 0.0f);
		scl = glm::vec3(1.0f, 1.0f, 1.0f);
	}

	vec3 pos;
	vec3 rot;
	vec3 scl;

	mat4 GetMatrix();
	void Rotate(float x, float y, float z);
	void Translate(float x, float y, float z);
	void Translate(vec3 _pos);
	void Scale(float x, float y, float z);
	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void SetScale(float x, float y, float z);
	mat4 GetRotMatrix();
	mat4 GetTransMatrix();
	mat4 GetScaleMatrix();
};