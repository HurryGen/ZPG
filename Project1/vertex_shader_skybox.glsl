#version 450
layout(location = 0) in vec3 vp;


uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMat;
uniform mat4 projectionMatrix;
uniform bool isFreezed;
out vec3 fragmentLocalPosition;

void main () {
	
	

	mat4 viewMatrixEdited;
	if(!isFreezed){
		viewMatrixEdited = mat4(mat3(viewMatrix));
	}else{
		viewMatrixEdited = viewMatrix * modelMat ;
		
	}
	gl_Position = projectionMatrix * viewMatrixEdited * vec4(vp, 1.0);

	

	
	 
	 //gl_Position = projectionMatrix * viewMatrix *modelMatrix* vec4(vp, 1.0);
	//gl_Position = projectionMatrix * viewMatrixEdited * vec4(vp, 1.0);
	
	 
	 fragmentLocalPosition = vp;


}
