#version 330 core

in vec3 fragNormal;
out vec4 frag_colour;

struct Light {
    vec3 position;
    vec4 color;
};

uniform int numLights;
uniform Light lights[100];

void main() {
    vec3 normal = normalize(fragNormal);
    vec4 totalDiffuse = vec4(0.0);

    for (int i = 0; i < numLights; ++i) {
        vec3 lightDir = normalize(lights[i].position - fragNormal);
        float diff = max(dot(normal, lightDir), 0.0);
        
        totalDiffuse += lights[i].color * diff;
    }

    frag_colour = totalDiffuse;
}
