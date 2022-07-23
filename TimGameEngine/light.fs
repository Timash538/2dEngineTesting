#version 330 core

in vec3 FragPos;
uniform vec3 Pos;
uniform float Size;
uniform vec3 Color;
uniform vec3 bColor;
uniform vec3 SelfColor;

out vec4 FragColor;

void main() {
    
    FragColor = vec4(1.0f,1.0f,1.0f,(1-distance(FragPos,Pos)/Size));
}