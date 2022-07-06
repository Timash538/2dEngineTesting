#version 330 core

layout (location = 0) in vec3 aPos;
uniform vec3 Pos;
uniform vec3 res;
uniform vec3 cam;
uniform vec3 scene;

void main() {
	vec3 newPos = (aPos+Pos-cam);
	newPos = vec3(newPos.x/(scene.x/2),newPos.y/(scene.y/2),newPos.z);
	gl_Position = vec4(newPos, 1.0);
}