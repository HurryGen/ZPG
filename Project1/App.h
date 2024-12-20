#ifndef APP_H
#define APP_H

#include "ShaderProgram.h"
#include "Model.h"
#include <GLFW/glfw3.h>
#include "DrawableObject.h"
#include "Scene.h"
#include "Camera.h"
#include "Transformation.h"
#include "TransformationComponent.h"
#include "Light.h"

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <cmath>
#include <iostream>



class App {
public:
	App();
	~App();
	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	void cursor_callback(GLFWwindow* window, double x, double y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);
	void initialization();
	void createShaders();
	void createModels();
	void createScenes();
	void createCameras();
	void run();

private:
	GLFWwindow* window;
	bool lockMouse = false;
};

#endif
