#version 330 core

layout (location = 0) in vec3 aPos;
uniform vec3 Pos;

void main() {
	vec3 newPos = aPos+Pos;
	gl_Position = vec4(newPos, 1.0);
}