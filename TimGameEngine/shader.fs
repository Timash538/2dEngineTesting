#version 330 core

//in vec2 TexCoord;
//in vec3 Normal;
in vec3 FragPos;
uniform vec3 Postix;


out vec4 FragColor;

/*uniform struct material {
sampler2D texture_diffuse1;
sampler2D texture_specular1;
float shininess;
} damn;

struct light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};*/



/*uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 objectColor;
uniform vec3 lightColor;
*/

/*float circle(float radius, vec2 position) {
    float value = distance(position,vec2(0.7,0.5));
    return step(radius,value);
    }*/

void main() {
    //vec2 pixelCoord = gl_FragCoord.xy/vec2(800.0,800.0);
    //float circleWidth = 0.2;
    //float circleA = circle(circleWidth,pixelCoord);
    //vec3 color = vec3(circleA);
    gl_FragColor = vec4(1.0,0.0,0.0,1.0);
}