#version 450


in vec3 fragmentLocalPosition;


layout(binding = 0) uniform samplerCube myCubeMap;


out vec4 frag_colour;



void main () {
	 
    frag_colour = texture(myCubeMap, fragmentLocalPosition);
    //frag_colour = vec4(1.0, 0.0, 0.0, 1.0);
}

