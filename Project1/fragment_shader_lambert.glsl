#version 400
in vec3 fragPosition;
in vec3 fragNormal;
out vec4 fragColor;

uniform vec3 lightPosition;
uniform vec4 lightColor;
uniform vec4 ambient = vec4(0.25f, 0.25f, 0.25f, 1.0f);

void main(void)
{
    vec3 normal = normalize(fragNormal);
    vec3 lightDir = normalize(lightPosition - fragPosition);
    
    
    float diffIntensity = max(dot(normal, lightDir), 0.0);
    vec4 diffuseColor = diffIntensity * lightColor;

    
    vec4 objectColor = vec4(0.8, 0.8, 0.8, 1.0);

    
    fragColor = ambient + diffuseColor * objectColor;
}
