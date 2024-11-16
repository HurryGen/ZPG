#version 330 core

in vec3 fragNormal;
in vec3 fragPosition;
out vec4 frag_colour;
uniform float specularStrength = 100.0;

struct Light {
    vec3 position;
    vec4 color;
};

uniform int numLights;
uniform Light lights[100];

void main() {
    vec4 totalSpecular = vec4(0.0);

    for (int i = 0; i < numLights; ++i) {
        vec3 normal = vec3(1);
        float spec = 100.f;
        vec4 specularColor = specularStrength * spec * lights[i].color;

        totalSpecular += specularColor;
    }

    frag_colour = totalSpecular;
}
