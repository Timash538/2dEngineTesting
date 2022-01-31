#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
uniform mat4 WVP;
uniform mat4 model;
uniform mat4 rotation;
uniform mat4 scale;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

void main() {
	gl_Position = WVP * vec4(aPos, 1.0);
	FragPos = vec3(model * vec4(aPos, 1.0));
	Normal = mat3(transpose(inverse(rotation * model))) * aNormal;
}