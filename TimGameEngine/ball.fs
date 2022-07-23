#version 330 core

in vec3 FragPos;
uniform vec3 Pos;
uniform float Size;
uniform vec3 Color;
uniform vec3 bColor;
uniform vec3 SelfColor;

out vec4 FragColor;

void main() {
    
    FragColor = (distance(FragPos,Pos)<Size) ? vec4(1.0f) : vec4(0.0f);
    if (FragColor.a == 0.0f) {
    discard;
    }
}