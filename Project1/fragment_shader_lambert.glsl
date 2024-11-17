#version 400
in vec3 fragPosition;
in vec3 fragNormal;
out vec4 fragColor;

uniform vec4 ambient = vec4(0.25, 0.25, 0.25, 1.0);

struct Light {
    vec3 position;
    vec4 color;
    vec3 spotDir;
    float cutoff;
    int mode; // 0: Point light, 1: Spotlight
};

struct Material {
    vec3 ra; // Ambient reflection
    vec3 rd; // Diffuse reflection
};

uniform Material material;
uniform int numLights;
uniform Light lights[100];

float attenuation(float c, float l, float q, float dist) {
    float att = 1.0 / (c + l * dist + q * dist * dist);
    return clamp(att, 0.0, 1.0);
}

void main(void)
{
    vec3 normal = normalize(fragNormal);
    vec4 totalDiffuse = vec4(0.0);

    for (int i = 0; i < numLights; ++i) {
        vec3 lightDir = normalize(lights[i].position - fragPosition);
        float distance = length(lights[i].position - fragPosition);
        float att = attenuation(1.0, 0.018, 0.005, distance);

        if (lights[i].mode == 0) {
            // Point light
            float diffIntensity = max(dot(normal, lightDir), 0.0);
            vec4 diffuseColor = diffIntensity * lights[i].color * vec4(material.rd, 1.0);
            totalDiffuse += diffuseColor * att;
        } else if (lights[i].mode == 1) {
            // Spotlight
            float cutoff = cos(radians(lights[i].cutoff));
            float theta = dot(normalize(-lightDir), lights[i].spotDir);

            if (theta > cutoff) {
                float diffIntensity = max(dot(normal, lightDir), 0.0);
                vec4 diffuseColor = diffIntensity * lights[i].color * vec4(material.rd, 1.0);

                float intense = (theta - cutoff) / (1.0 - cutoff);
                intense = clamp(intense, 0.0, 1.0);
                totalDiffuse += diffuseColor * intense * att;
            }
        }else if(lights[i].mode == 2){
            // Directional light
            lightDir = normalize(-lights[i].spotDir);
            float diffIntensity = max(dot(normal, lightDir), 0.0);
            vec4 diffuseColor = diffIntensity * lights[i].color * vec4(material.rd, 1.0);
            totalDiffuse += diffuseColor;
        }
    }

    vec4 ambientColor = vec4(material.ra, 1.0) * ambient;
    fragColor = ambientColor + totalDiffuse;
}
