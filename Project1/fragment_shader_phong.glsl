#version 400
in vec3 fragPosition;
in vec3 fragNormal;
out vec4 fragColor;

uniform vec4 ambient = vec4(0.0, 0.0, 0.0, 0.0);
uniform vec3 cameraPosition;
uniform float specularStrength = 70.0;


struct Light {
    vec3 position;
    vec4 color;
    vec3 spotDir;
    float cutoff;
    int mode;
};

uniform int numLights;
uniform Light lights[100];

void main(void)
{
    vec3 normal = normalize(fragNormal);
    vec3 viewDir = normalize(cameraPosition - fragPosition);

    vec4 objectColor = vec4(0.8, 0.8, 0.8, 1.0);
    vec4 totalDiffuse = vec4(0.0);
    vec4 totalSpecular = vec4(0.0);

    for (int i = 0; i < numLights; ++i) {
        vec3 lightDir = normalize(lights[i].position - fragPosition);


        if (lights[i].mode == 0) {
            float diffIntensity = max(dot(normal, lightDir), 0.0);
            vec4 diffuseColor = diffIntensity * lights[i].color;
            totalDiffuse += diffuseColor;


            if (diffIntensity > 0.0) {
                vec3 reflectDir = reflect(-lightDir, normal);
                float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
                vec4 specularColor = specularStrength * spec * lights[i].color;
                totalSpecular += specularColor;
            }
        }else if(lights[i].mode == 1){
            
            float cutoff = cos(radians (lights[i].cutoff));
            float theta = dot(normalize(-lightDir), lights[i].spotDir);

            
            if (theta > cutoff) {
               
                float diffIntensity = max(dot(normal, lightDir), 0.0);
                vec4 diffuseColor = diffIntensity * lights[i].color;
                
                float intense = (theta - cutoff) / (1.0 - cutoff);
                intense = clamp(intense, 0.0, 1.0);
                totalDiffuse += diffuseColor * intense;

                
                if (diffIntensity > 0.0) {
                    vec3 reflectDir = reflect(-lightDir, normal);
                    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
                    vec4 specularColor = specularStrength * spec * lights[i].color;
                    totalSpecular += specularColor;
                }
            }
           
        }
           
    }


    fragColor = ambient + (totalDiffuse + totalSpecular) * objectColor;
}