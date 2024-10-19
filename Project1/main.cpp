//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>


//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include "App.h"
int main(void)
{
	App* app = new App();
	app->initialization(); //OpenGL inicialization

	//Loading scene
	app->createShaders();
	app->createModels();
	app->createScenes();
	app->run(); //Rendering 
}