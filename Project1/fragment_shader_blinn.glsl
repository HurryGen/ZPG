#version 400
in vec3 fragPosition;
in vec3 fragNormal;
out vec4 fragColor;

uniform vec3 lightPosition;
uniform vec4 lightColor;
uniform vec4 ambient = vec4(0.25f, 0.25f, 0.25f, 1.0f);
uniform vec3 viewDir = vec3(0.0f, 0.0f, 1.0f);
uniform float specularStrength = 70.0f;

void main(void)
{
    vec3 normal = normalize(fragNormal);
    vec3 lightDir = normalize(lightPosition - fragPosition);
    float diffIntensity = max(dot(normal, lightDir), 0.0);
   
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

    vec4 objectColor = vec4(0.8, 0.8, 0.8, 1.0);

    vec4 diffuseColor = diffIntensity * lightColor;
    vec4 specularColor = specularStrength * spec * lightColor;

    fragColor = ambient + (diffuseColor + specularColor) * objectColor;
}
