#version 330 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

//uniform struct Material {
//sampler2D diffuse;
//sampler2D specular;
//float shininess;
//};



uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 objectColor;
uniform vec3 lightColor;


void main() {
float ambientStrength = 0.1;

vec3 ambient = ambientStrength * lightColor;

vec3 norm = normalize(Normal);
vec3 lightDir = normalize(lightPos - FragPos);
float diff = max(dot(norm,lightDir),0.0);
vec3 diffuse = diff*lightColor;

float specularStrength = 0.5;
vec3 viewDir = normalize(viewPos - FragPos);
vec3 reflectDir = reflect(-lightDir, norm);
float spec = pow(max(dot(viewDir,reflectDir),0.0),32);
vec3 specular = vec3(0.0);

if (dot(norm, lightDir) >= 0.0f) {
    specular = specularStrength * spec * lightColor;
}
    vec3 result = (ambient+ diffuse +specular) * objectColor;
    FragColor = vec4(result, 1.0);
}