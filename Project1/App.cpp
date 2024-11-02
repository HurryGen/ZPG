#include "App.h"
#include "../Models/tree.h"
#include "../Models/bushes.h"
#include "../Models/gift.h"
#include "../Models/sphere.h"

ShaderProgram* shader;
ShaderProgram* shader1;
ShaderProgram* shaderWithLight;
ShaderProgram* shaderWithLight1;
Model* treeModel;
Model* bushModel;
Model* giftModel;
Model* triangleModel;
Model* sphereModel;

Scene* scene1;
Scene* scene2;
Scene* scene;
Camera* camera;


App::App() {
	
}



void App::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void App::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void App::window_focus_callback(GLFWwindow* window, int focused)
{
	printf("window_focus_callback \n");
}

void App::window_iconify_callback(GLFWwindow* window, int iconified)
{
	printf("window_iconify_callback \n");
}

void App::window_size_callback(GLFWwindow* window, int width, int height)
{
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void App::cursor_callback(GLFWwindow* window, double x, double y)
{
	printf("cursor_callback \n");
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	float xoffset = x - (width / 2);
	float yoffset = (height / 2) - y;

	glfwSetCursorPos(window, width / 2, height / 2);

	camera->updatePosition(xoffset, yoffset);
	
	
}




void App::button_callback(GLFWwindow* window, int button, int action, int mode)
{
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}

void App::initialization()
{
	
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	/* //inicializace konkretni verze
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE,
	GLFW_OPENGL_CORE_PROFILE);  //*/

	window = glfwCreateWindow(1600, 1200, "ZPG", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();


	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);
	glfwSetKeyCallback(window, key_callback);
	//glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetMouseButtonCallback(window, button_callback);
	glfwSetWindowFocusCallback(window, window_focus_callback);
	glfwSetWindowIconifyCallback(window, window_iconify_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);
	

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetCursorPos(window, width / 2, height / 2);
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
		App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
		if (app) {
			app->cursor_callback(window,xpos, ypos);
		}
		});

	glfwSetWindowUserPointer(window, this);

}




void App::createShaders()
{
	shader = new ShaderProgram("vertex_shader_camera.glsl","fragment_shader_camera.glsl");
	shader1 = new ShaderProgram("vertex_shader.glsl", "fragment_shader.glsl");
	shaderWithLight = new ShaderProgram("vertex_shader_light.glsl", "fragment_shader_light.glsl");
	shaderWithLight1 = new ShaderProgram("vertex_shader_light.glsl", "fragment_shader_phong.glsl");

	camera->attach(shader);
	camera->attach(shaderWithLight);
	camera->attach(shaderWithLight1);

	// Create a light source
	Light* light1 = new Light(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.f, 1.0f));
	Light* light2 = new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.f, 1.0f));
	
	


	light1->attach(shaderWithLight);
	light2->attach(shaderWithLight1);
	light1->notify();
	light2->notify();

}

void App::createModels()
{
	float points[] = {
	 0.0f, 0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,

	};

	treeModel = new Model(tree, sizeof(tree)/sizeof(tree[0]), GL_TRIANGLES, 0, sizeof(bushes));
	bushModel = new Model(bushes, sizeof(bushes) / sizeof(bushes[0]), GL_TRIANGLES, 0, sizeof(bushes));
	giftModel = new Model(gift, sizeof(gift) / sizeof(gift[0]), GL_TRIANGLES, 0, sizeof(gift));
	triangleModel = new Model(points, sizeof(points) / sizeof(points[0]), GL_TRIANGLES, 0, 3);
	sphereModel = new Model(sphere, sizeof(sphere) / sizeof(sphere[0]), GL_TRIANGLES, 0, sizeof(sphere));
}
void App::createCameras()
{
	camera = new Camera();
}

void App::createScenes()
{
	//Transformation transformation;
	scene1 = new Scene();
	scene2 = new Scene();
	scene = new Scene();
	scene->addObject(new DrawableObject(triangleModel, shader1));
	
	for (int i = 0; i < 100; i++) {
		std::srand(static_cast<unsigned int>(6646545+i*1000000));
		int lowerBoundAngle = -360;
		int upperBoundAngle = 360;
		int upperBound = 20;
		int lowerBound = -20;
		int upperBoundHeigth = 100;
		int lowerBoundHeigth = 10;
		float randAngle = (std::rand() % (upperBoundAngle - lowerBoundAngle + 1)) + lowerBoundAngle;
		float heigth = (float)((std::rand() % (upperBoundHeigth - lowerBoundHeigth + 1)) + lowerBoundHeigth)/100;
		float x = (float)((std::rand() % (upperBound - lowerBound + 1)) + lowerBound);
		float z = (float)((std::rand() % (upperBound - lowerBound + 1)) + lowerBound);
		DrawableObject* drawableTree = new DrawableObject(treeModel, shaderWithLight);
		Transformation transformation;

		auto translate = std::make_shared<Translate>(x, 0.f, z);
		transformation.add(translate);
		auto rotate = std::make_shared<Rotate>(randAngle, 0.0f, 1.0f, 0.0f);
		transformation.add(rotate);
		auto scale = std::make_shared<Scale>(0.5f * heigth, 0.5f * heigth, 0.5f * heigth);
		transformation.add(scale);
		drawableTree->setTransformation(transformation);
		scene1->addObject(drawableTree);
		
		
	}
	for (int i = 0; i < 100; i++) {
		std::srand(static_cast<unsigned int>(544565465654 + i * 100000));
		int lowerBoundAngle = -360;
		int upperBoundAngle = 360;
		int upperBound = 20;
		int lowerBound = -20;
		int upperBoundHeigth = 300;
		int lowerBoundHeigth = 10;
		float randAngle = (std::rand() % (upperBoundAngle - lowerBoundAngle + 1)) + lowerBoundAngle;
		float heigth = (float)((std::rand() % (upperBoundHeigth - lowerBoundHeigth + 1)) + lowerBoundHeigth) / 100;
		float x = (float)((std::rand() % (upperBound - lowerBound + 1)) + lowerBound);
		float z = (float)((std::rand() % (upperBound - lowerBound + 1)) + lowerBound);
		DrawableObject* drawableBush = new DrawableObject(bushModel, shaderWithLight);
		Transformation transformation;

		auto translate = std::make_shared<Translate>(x, 0.f, z);
		transformation.add(translate);
		auto rotate = std::make_shared<Rotate>(randAngle, 0.0f, 1.0f, 0.0f);
		transformation.add(rotate);
		auto scale = std::make_shared<Scale>(1.f * heigth, 1.f * heigth, 1.f * heigth);
		transformation.add(scale);
		drawableBush->setTransformation(transformation);
		scene1->addObject(drawableBush);


	}


	
	

	DrawableObject* drawableSphere1 = new DrawableObject(sphereModel, shaderWithLight1);
	Transformation transformation1;
	
	transformation1.add(std::make_shared <Translate>(1.f, 1.f, 0.f));
	drawableSphere1->setTransformation(transformation1);
	scene2->addObject(drawableSphere1);

	DrawableObject* drawableSphere2 = new DrawableObject(sphereModel, shaderWithLight1);
	Transformation transformation2;
	transformation2.add(std::make_shared <Translate>(-1.f, 1.f, 0.f));
	drawableSphere2->setTransformation(transformation2);
	scene2->addObject(drawableSphere2);

	DrawableObject* drawableSphere3 = new DrawableObject(sphereModel, shaderWithLight1);
	Transformation transformation3;
	transformation3.add(std::make_shared <Translate>(1.f, -1.f, 0.f));
	drawableSphere3->setTransformation(transformation3);
	scene2->addObject(drawableSphere3);

	DrawableObject* drawableSphere4 = new DrawableObject(sphereModel, shaderWithLight1);
	Transformation transformation4;
	transformation4.add(std::make_shared <Translate>(-1.f, -1.f, 0.f));
	drawableSphere4->setTransformation(transformation4);
	scene2->addObject(drawableSphere4);




	
	
}

void App::run()
{
	int sceneIndex = 0;
	
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window)) {
		//clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//model->draw(GL_TRIANGLES, 0, 3);
		//model->draw(GL_QUADS, 3, 4);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			camera->moveForward();
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			camera->moveBackward();
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			camera->moveLeft();
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			camera->moveRight();
		}
		

		if (sceneIndex == 0) {
			scene->render();
		}
		if (sceneIndex == 1) {
			scene1->render();
		}
		if (sceneIndex == 2) {
			scene2->render();
		}
		
		
		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
			sceneIndex = 0;
		}
		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
			sceneIndex = 1;
		}
		if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
			sceneIndex = 2;
		}
		
		
		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}
