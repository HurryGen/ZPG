#version 330 core

in vec3 fragNormal;
out vec4 frag_colour;
uniform vec4 lightColor;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;


void main() {
    vec3 lightDir = normalize(lightPosition-fragNormal);
    float diff = max(dot(normalize(fragNormal), lightDir), 0.0);

    frag_colour = vec4(lightColor * diff);
}