#include "App.h"
#include "../Models/tree.h"
#include "../Models/bushes.h"
#include "../Models/gift.h"
#include "../Models/sphere.h"
#include "../Models/suzi_smooth.h"
#include "../Models/plain.h"
#include "DynamicRotate.h"
#include "RandomTranslate.h"

ShaderProgram* shader;
ShaderProgram* shader1;
ShaderProgram* shaderWithLight;
ShaderProgram* shaderWithLight1;
ShaderProgram* shaderPhong;
ShaderProgram* shaderBlinn;
ShaderProgram* shaderLambert;
ShaderProgram* shaderConstant;



Model* treeModel;
Model* bushModel;
Model* giftModel;
Model* triangleModel;
Model* sphereModel;
Model* suziSmoothModel;
Model* plainModel;

Scene* scene1;
Scene* scene2;
Scene* scene3;
Scene* scene4;
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
	// if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	// 	glfwSetWindowShouldClose(window, GL_TRUE);
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
	camera->updateAspect(width, height);
}

void App::cursor_callback(GLFWwindow* window, double x, double y)
{
	if(lockMouse)
	{
		return;
	}
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

	window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
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
	

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
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
	shaderPhong = new ShaderProgram("vertex_shader_light.glsl", "fragment_shader_phong.glsl");
	shaderBlinn = new ShaderProgram("vertex_shader_light.glsl", "fragment_shader_blinn.glsl");
	shaderLambert = new ShaderProgram("vertex_shader_light.glsl", "fragment_shader_lambert.glsl");
	shaderConstant = new ShaderProgram("vertex_shader_light.glsl", "fragment_shader_light.glsl");

}

void App::createModels()
{
	float points[] = {
	0.0f, 0.5f, 0.0f, 0,0,0,
	0.5f, -0.5f, 0.0f, 0,0,0,
   - 0.5f, -0.5f, 0.0f, 0,0,0,
	};

	treeModel = new Model(tree, sizeof(tree)/sizeof(tree[0]), GL_TRIANGLES, 0, sizeof(bushes));
	bushModel = new Model(bushes, sizeof(bushes) / sizeof(bushes[0]), GL_TRIANGLES, 0, sizeof(bushes));
	giftModel = new Model(gift, sizeof(gift) / sizeof(gift[0]), GL_TRIANGLES, 0, sizeof(gift));
	triangleModel = new Model(points, sizeof(points) / sizeof(points[0]), GL_TRIANGLES, 0, 3);
	sphereModel = new Model(sphere, sizeof(sphere) / sizeof(sphere[0]), GL_TRIANGLES, 0, sizeof(sphere));
	suziSmoothModel = new Model(suziSmooth, sizeof(suziSmooth) / sizeof(suziSmooth[0]), GL_TRIANGLES, 0, sizeof(suziSmooth));
	plainModel = new Model(plain, sizeof(plain) / sizeof(plain[0]), GL_TRIANGLES, 0, sizeof(plain));
	
}
void App::createCameras()
{
	camera = new Camera();
}



void App::createScenes()
{
	Light* light1 = new Light(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec4(0.5f, 0.5f, 1.f, 1.0f), glm::vec3(0.05f, -1.0f, 0.0f), 25.f);
	Light* light2 = new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.f, 1.0f));
	Light* light3 = new Light(glm::vec3(3.0f, 2.0f, 8.0f), glm::vec4(0.5f, 0.5f, 1.f, 1.0f));
	//Transformation transformation;
	scene1 = new Scene();
	scene2 = new Scene();
	scene3 = new Scene();
	scene4 = new Scene();
	scene = new Scene();


	

	scene1->setCamera(camera);
	scene2->setCamera(camera);
	scene3->setCamera(camera);
	scene4->setCamera(camera);
	camera->attach(light1);


	scene1->addLight(light1);
	scene1->addLight(light3);
	scene2->addLight(light2);
	scene3->addLight(light3);
	scene3->addLight(light1);
	scene2->addLight(light1);
	scene4->addLight(light1);
	
	light1->attach(shaderPhong);
	light1->attach(shaderBlinn);
	light1->attach(shaderLambert);
	light1->attach(shaderConstant);
	light2->attach(shaderPhong);
	light2->attach(shaderBlinn);
	light2->attach(shaderLambert);
	light2->attach(shaderConstant);
	light3->attach(shaderPhong);
	light3->attach(shaderBlinn);
	light3->attach(shaderLambert);
	light3->attach(shaderConstant);

	scene->addObject(new DrawableObject(triangleModel, shader1));

	DrawableObject* drawablePlain = new DrawableObject(plainModel, shaderPhong);
	Transformation transformationPlain;
	transformationPlain.add(std::make_shared <Translate>(0.f, 0.f, 0.f));
	transformationPlain.add(std::make_shared <Scale>(50.f, 50.f, 50.f));
	drawablePlain->setTransformation(transformationPlain);
	scene1->addObject(drawablePlain);
	
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
		DrawableObject* drawableTree = new DrawableObject(treeModel, shaderPhong);
		Transformation transformation;

		auto autoRotate = std::make_shared<DynamicRotate>(1.f,0.f, 1.f, 0.f);
		
		auto translate = std::make_shared<Translate>(x, 0.f, z);
		transformation.add(translate);
		transformation.add(autoRotate);
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
		DrawableObject* drawableBush = new DrawableObject(bushModel, shaderPhong);
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

	for (int i = 0; i < 20; i++) {

		DrawableObject* drawableSuziSmooth = new DrawableObject(suziSmoothModel, shaderPhong);
		Transformation transformation;
		int upperBound = 20;
		int lowerBound = -20;

		float x = (float)((std::rand() % (upperBound - lowerBound + 1)) + lowerBound);
		float z = (float)((std::rand() % (upperBound - lowerBound + 1)) + lowerBound);
		auto translate = std::make_shared <RandomTranslate>(5.f, x, 0.0f, z);
		translate->setBoundsX(-5.f, 5.f);
		translate->setBoundsY(1.f, 5.f);
		translate->setBoundsZ(-5.f, 5.f);
		transformation.add(translate);
		auto scale = std::make_shared<Scale>(0.2f, 0.2f, 0.2f);
		transformation.add(scale);
		drawableSuziSmooth->setTransformation(transformation);
		
		scene1->addObject(drawableSuziSmooth);
	}


	
	

	DrawableObject* drawableSphere1 = new DrawableObject(sphereModel, shaderPhong);
	Transformation transformation1;
	
	transformation1.add(std::make_shared <Translate>(1.5f, 1.5f, 0.f));
	drawableSphere1->setTransformation(transformation1);
	scene2->addObject(drawableSphere1);

	DrawableObject* drawableSphere2 = new DrawableObject(sphereModel, shaderPhong);
	Transformation transformation2;
	transformation2.add(std::make_shared <Translate>(-1.5f, 1.5f, 0.f));
	drawableSphere2->setTransformation(transformation2);
	scene2->addObject(drawableSphere2);

	DrawableObject* drawableSphere3 = new DrawableObject(sphereModel, shaderPhong);
	Transformation transformation3;
	transformation3.add(std::make_shared <Translate>(1.5f, -1.5f, 0.f));
	drawableSphere3->setTransformation(transformation3);
	scene2->addObject(drawableSphere3);

	DrawableObject* drawableSphere4 = new DrawableObject(sphereModel, shaderPhong);
	Transformation transformation4;
	transformation4.add(std::make_shared <Translate>(-1.5f, -1.5f, 0.f));
	drawableSphere4->setTransformation(transformation4);
	scene2->addObject(drawableSphere4);

	

	DrawableObject* drawableGift = new DrawableObject(giftModel, shaderPhong);
	DrawableObject* drawableSuziSmooth = new DrawableObject(suziSmoothModel, shaderBlinn);
	DrawableObject* drawableTree = new DrawableObject(treeModel, shaderConstant);
	DrawableObject* drawableSphere = new DrawableObject(sphereModel, shaderLambert);
	Transformation transformationGift;
	Transformation transformationSuziSmooth;
	Transformation transformationTree;
	Transformation transformationSphere;
	transformationGift.add(std::make_shared <Translate>(-3.f, -1.f, -4.f));
	transformationGift.add(std::make_shared <Scale>(5.f, 5.f, 5.f));
	transformationSuziSmooth.add(std::make_shared <Translate>(0.f, 0.f, -4.f));
	transformationTree.add(std::make_shared <Translate>(6.f, -1.f, -4.f));
	transformationSphere.add(std::make_shared <Translate>(3.f, 0.f, -4.f));
	drawableGift->setTransformation(transformationGift);
	drawableSuziSmooth->setTransformation(transformationSuziSmooth);
	drawableTree->setTransformation(transformationTree);
	drawableSphere->setTransformation(transformationSphere);

	scene3->addObject(drawableGift);
	scene3->addObject(drawableSuziSmooth);
	scene3->addObject(drawableTree);
	scene3->addObject(drawableSphere);
	DrawableObject* drawableTreeRotate = new DrawableObject(treeModel, shaderBlinn);
	Transformation transformationTreeRotate;
	auto dynamicRotate = std::make_shared<DynamicRotate>(1.0f, 0.0f, 1.0f, 0.0f);
	auto randomTranslate = std::make_shared <RandomTranslate>(5.f,0.0f, 0.0f, 0.0f);

	transformationTreeRotate.add(randomTranslate);
	transformationTreeRotate.add(dynamicRotate);
	
	
	drawableTreeRotate->setTransformation(transformationTreeRotate);


	scene4->addObject(drawableTreeRotate);

	
	
	scene1->cameraInit();
	scene2->cameraInit();
	scene3->cameraInit();
	scene4->cameraInit();



	

	
	
	



	
	
	
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
		if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE){
			lockMouse = true;
		}
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
			lockMouse = false;
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
		if (sceneIndex == 3) {
			scene3->render();
		}
		if (sceneIndex == 4) {
			scene4->render();	
		}
		
		
		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
			sceneIndex = 0;
		}
		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
			scene1->lightsInit();
			sceneIndex = 1;
		}
		if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
			scene2->lightsInit();
			sceneIndex = 2;
		}
		if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
			scene3->lightsInit();
			sceneIndex = 3;
		}
		if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
			scene4->lightsInit();
			sceneIndex = 4;
		}
		
		
		// update other events like input handling
		glfwPollEvents();
		// put the stuff we�ve been drawing onto the display
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}
