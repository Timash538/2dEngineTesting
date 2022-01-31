#include "camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "tim_utils.h"

mat4 Camera::GetMatrix() {
	mat4 cameraTransform = lookAtLH(m_pos, m_pos - direction, vec3(0.0f, 1.0f, 0.0f));
	return cameraTransform;
}

void Camera::OnKeyboard(unsigned char key, float camSpeed) {
	if (key == 'w') {
		m_pos += camSpeed * direction;
	}
	if (key == 's') {
		m_pos -= camSpeed * direction;
	}
	if (key == 'a') {
		m_pos -= camSpeed * normalize(cross(direction,vec3(0.0f,1.0f,0.0f)));
	}
	if (key == 'd') {
		m_pos += camSpeed * normalize(cross(direction, vec3(0.0f, 1.0f, 0.0f)));
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