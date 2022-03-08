#pragma once
#include "glm/mat4x4.hpp"
#include "world_transform.h"

using namespace glm;

class Camera {
public:
	mat4 GetMatrix();
	void OnKeyboard(unsigned char key);
	void OnKeyboardUp(unsigned char key);
	void OnMouse(int x, int y);
	vec3 GetPosition();
	vec3 GetSpeed();
	void SetSpeed(vec3 speed);
	void SetPosition(vec3 position);
	void Update();
private:
	void Rotate();
	void Translate(float x, float y, float z);

	vec3 m_pos = vec3(0.0f,0.0f,0.0f);
	vec3 speed = vec3(0.0f, 0.0f, 0.0f);
	vec3 direction = vec3(0.0f,0.0f,1.0f);
	float pitch, yaw=90.0f, roll;
};