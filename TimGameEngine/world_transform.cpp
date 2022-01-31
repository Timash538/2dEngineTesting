#include "world_transform.h"
#include "glm/gtx/transform.hpp"
#include "tim_utils.h"

#define GLM_FORCE_LEFT_HANDED

using namespace glm;

mat4 InitRotationTransform(vec3 rot);

mat4 WorldTransform::GetMatrix() {

	mat4 translation = translate(pos);
	mat4 rotation = InitRotationTransform(rot);
	mat4 scaling = scale(scl);

	return translation * rotation * scaling;
}


void WorldTransform::Translate(float x, float y, float z) {
	pos.x += x;
	pos.y += y;
	pos.z += z;
}

void WorldTransform::Translate(vec3 _pos) {
	pos.x += _pos.x;
	pos.y += _pos.y;
	pos.z += _pos.z;
}

void WorldTransform::Rotate(float x, float y, float z) {
	rot.x += x;
	rot.y += y;
	rot.z += z;
}

void WorldTransform::Scale(float x, float y, float z) {
	scl.x += x;
	scl.y += y;
	scl.z += z;
}

void WorldTransform::SetPosition(float x, float y, float z) {
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

void WorldTransform::SetRotation(float x, float y, float z) {
	rot.x = x;
	rot.y = y;
	rot.z = z;
}

void WorldTransform::SetScale(float x, float y, float z) {
	scl.x = x;
	scl.y = y;
	scl.z = z;
}

mat4 WorldTransform::GetRotMatrix() {
	mat4 rotation = InitRotationTransform(rot);
	return rotation;
}

mat4 WorldTransform::GetTransMatrix() {
	mat4 translation = translate(pos);
	return translation;
}

mat4 WorldTransform::GetScaleMatrix() {
	mat4 scaling = scale(scl);
	return scaling;
}
