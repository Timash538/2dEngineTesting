#include "camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "tim_utils.h"

mat4 Camera::GetMatrix() {
	mat4 cameraTransform = lookAtLH(m_pos, m_pos - direction, vec3(0.0f, 1.0f, 0.0f));
	return cameraTransform;
}

void Camera::OnKeyboard(unsigned char key) {
	float scale = 0.4f;
	if (key == 'w') {
		speed.z = scale;
	}
	if (key == 's') {
		speed.z = -scale;
	}
	if (key == 'a') {
		speed.x = -scale;
	}
	if (key == 'd') {
		speed.x = scale;
	}
}

void Camera::OnKeyboardUp(unsigned char key) {
	if (key == 'w' || key == 's') {
		speed.z = 0.0f;
	}
	if (key == 'a' || key == 'd') {
		speed.x = 0.0f;
	}
}

void Camera::OnMouse(int x, int y) {
	yaw -= x*0.1f;
	pitch += y*0.1f;
	if (pitch > 89.9f)
		pitch = 89.9f;
	if (pitch < -89.9f)
		pitch = -89.9f;
	Rotate();
}

void Camera::Rotate() {
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
}

void Camera::Translate(float x, float y, float z) {

}

vec3 Camera::GetPosition() {
	return m_pos;
}

void Camera::SetPosition(vec3 s) {}

vec3 Camera::GetSpeed() {
	return speed;
}

void Camera::SetSpeed(vec3 speedN) {
	speed = speedN;
}

void Camera::Update() {
		m_pos += speed.z * direction;
		m_pos += speed.x * normalize(cross(direction, vec3(0.0f, 1.0f, 0.0f)));	
}