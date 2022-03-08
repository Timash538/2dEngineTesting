#version 330 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform struct material {
sampler2D texture_diffuse1;
sampler2D texture_specular1;
float shininess;
} damn;

struct light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};



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
    //FragColor = vec4(result, 1.0);
    FragColor = texture(damn.texture_diffuse1, TexCoord);
}