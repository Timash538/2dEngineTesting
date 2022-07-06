#version 330 core

in vec3 FragPos;
uniform vec3 Pos;
uniform vec3 Color;
uniform vec3 SelfColor;

out vec4 FragColor;

void main() {
    FragColor = vec4(SelfColor*Color,1.0f);
}