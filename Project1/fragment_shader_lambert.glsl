#version 400
in vec3 fragPosition;
in vec3 fragNormal;
out vec4 fragColor;

uniform vec4 ambient = vec4(0.25, 0.25, 0.25, 1.0);

struct Light {
    vec3 position;
    vec4 color;
};

uniform int numLights;
uniform Light lights[100];

void main(void)
{
    vec3 normal = normalize(fragNormal);
    vec4 objectColor = vec4(0.8, 0.8, 0.8, 1.0);
    vec4 totalDiffuse = vec4(0.0);

    for (int i = 0; i < numLights; ++i) {
        vec3 lightDir = normalize(lights[i].position - fragPosition);

        // Calculate diffuse component
        float diffIntensity = max(dot(normal, lightDir), 0.0);
        vec4 diffuseColor = diffIntensity * lights[i].color;

        // Accumulate each light's diffuse contribution
        totalDiffuse += diffuseColor;
    }

    fragColor = ambient + totalDiffuse * objectColor;
}
