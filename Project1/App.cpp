#include "App.h"

#include "AssimpModel.h"
#include "BezierTranslate.h"
#include "DrawableLight.h"
#include "../Models/tree.h"
#include "../Models/bushes.h"
#include "../Models/gift.h"
#include "../Models/sphere.h"
#include "../Models/suzi_smooth.h"
#include "../Models/plain.h"
#include "DynamicRotate.h"
#include "ModelFactory.h"
#include "RandomTranslate.h"
#include "SceneController.h"
#include "SkyCube.h"
#include "TextureModel.h"
#include "../Models/plainTexture.h"

ShaderProgram* shader;
ShaderProgram* shader1;
ShaderProgram* shaderWithLight;
ShaderProgram* shaderWithLight1;
ShaderProgram* shaderPhong;
ShaderProgram* shaderBlinn;
ShaderProgram* shaderLambert;
ShaderProgram* shaderConstant;
ShaderProgram* shaderDrawableLight;
ShaderProgram* shaderPhongTexture;




AbstractModel* treeModel;
AbstractModel* bushModel;
AbstractModel* giftModel;
AbstractModel* triangleModel;
AbstractModel* sphereModel;
AbstractModel* suziSmoothModel;
AbstractModel* plainModel;
AbstractModel* loginModel;
AbstractModel* houseModel;
AbstractModel* dogModel;
AbstractModel* plainTextureModel;
AbstractModel* plainDenseTextureModel;
AbstractModel* textureTreeModel;


Scene* scene1;
Scene* scene2;
Scene* scene3;
Scene* scene4;
Scene* scene;
Camera* camera;

SceneController* sceneController = new SceneController();





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
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		ypos = height - ypos;

		GLuint stencilValue;
		float depth;
		glReadPixels(static_cast<int>(xpos), static_cast<int>(ypos), 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &stencilValue);
		glReadPixels(static_cast<int>(xpos), static_cast<int>(ypos), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		glm::vec3 p = glm::unProject(glm::vec3(xpos, ypos, depth), camera->getCamera(), camera->getProjection(), glm::vec4(0, 0, width, height));
		

		if (stencilValue > 0)
		{
			std::cout << "Vybrany objekt s ID: " << stencilValue << std::endl;
			std::cout << "Pozice: " << p.x << " " << p.y << " " << p.z << std::endl;
			sceneController->spawnObject(new DrawableObject(sphereModel, shaderPhong, new Material(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.7f, 0.7f, 0.7f), glm::vec3(0.0f, 0.0f, 0.0f))), p);
		}
	}
	if(button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		ypos = height - ypos;

		GLuint stencilValue;
		glReadPixels(static_cast<int>(xpos), static_cast<int>(ypos), 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &stencilValue);
		if (stencilValue > 0)
		{
			sceneController->removeObject(stencilValue);
		}
	}
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
	shaderDrawableLight = new ShaderProgram("vertex_shader_light.glsl", "fragment_shader_drawable_light.glsl");
	shaderPhongTexture = new ShaderProgram("vertex_shader_texture.glsl", "fragment_shader_phong_texture.glsl");

}

void App::createModels()
{
	float points[] = {
	0.0f, 0.5f, 0.0f, 0,0,0,
	0.5f, -0.5f, 0.0f, 0,0,0,
   - 0.5f, -0.5f, 0.0f, 0,0,0,
	};

	treeModel = ModelFactory::createModel(ModelType::BASIC, tree, sizeof(tree) / sizeof(bushes[0]),GL_TRIANGLES);
	bushModel = ModelFactory::createModel(ModelType::BASIC, bushes, sizeof(bushes) / sizeof(bushes[0]), GL_TRIANGLES);
	giftModel = ModelFactory::createModel(ModelType::BASIC, gift, sizeof(gift) / sizeof(gift[0]), GL_TRIANGLES);
	triangleModel = ModelFactory::createModel(ModelType::BASIC, points, sizeof(points) / sizeof(points[0]), GL_TRIANGLES);
	sphereModel = ModelFactory::createModel(ModelType::BASIC, sphere, sizeof(sphere) / sizeof(sphere[0]), GL_TRIANGLES);
	suziSmoothModel = ModelFactory::createModel(ModelType::BASIC, suziSmooth, sizeof(suziSmooth) / sizeof(suziSmooth[0]), GL_TRIANGLES);
	plainModel = ModelFactory::createModel(ModelType::BASIC, plain, sizeof(plain) / sizeof(plain[0]), GL_TRIANGLES);
	plainTextureModel = ModelFactory::createModel(ModelType::TEXTURE,plainTexture, sizeof(plainTexture) / sizeof(plainTexture[0]), GL_TRIANGLES);
	plainDenseTextureModel = ModelFactory::createModel(ModelType::TEXTURE,plainDenseTexture, sizeof(plainDenseTexture) / sizeof(plainDenseTexture[0]), GL_TRIANGLES);
	houseModel = ModelFactory::createModel("../Models/house.obj", GL_TRIANGLES);
	loginModel = ModelFactory::createModel("../Models/login.obj", GL_TRIANGLES);
	dogModel = ModelFactory::createModel("../Models/dog.obj", GL_TRIANGLES);
	textureTreeModel = ModelFactory::createModel("../Models/tree.obj", GL_TRIANGLES);
	
	
}
void App::createCameras()
{
	camera = new Camera();
	sceneController->setCamera(camera);
}



void App::createScenes()
{
	
	Light* light1 = new Light(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec4(1.0f, 1.0f, 2.f, 1.0f),glm::vec3(1.0, 0.018, 0.005) ,glm::vec3(0.05f, -1.0f, 0.0f), 25.f);
	Light* light2 = new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.f, 1.0f), glm::vec3(1.0, 0.018, 0.005));
	Light* light3 = new Light(glm::vec3(3.0f, 2.0f, 8.0f), glm::vec4(1.0f, 1.0f, 1.f, 1.0f), glm::vec3(1.0, 0.018, 0.005));
	Light* directionLight = new Light(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 1.0f));
	Material* matteMaterial = new Material(glm::vec3(0.f,0.f,0.f), glm::vec3(0.7f, 0.7f, 0.7f), glm::vec3(0.0f, 0.0f, 0.0f));
	Material* shinyMaterial = new Material(glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f));
	Material* glowingMaterial = new Material(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.9f, 0.9f, 0.9f), glm::vec3(2.0f, 2.0f, 2.0f));
	Material* grassMaterial = new Material(glm::vec3(0.f,0.f,0.f), glm::vec3(0.7f, 0.7f, 0.7f), glm::vec3(0.0f, 0.0f, 0.0f), "../Models/grass.png", 1);
	Material* woodMaterial = new Material(glm::vec3(0.f,0.f,0.f), glm::vec3(0.7f, 0.7f, 0.7f), glm::vec3(0.0f, 0.0f, 0.0f), "../Models/wooden_fence.png", 2);
	Material* houseMaterial = new Material(glm::vec3(0.f,0.f,0.f), glm::vec3(0.7f, 0.7f, 0.7f), glm::vec3(0.0f, 0.0f, 0.0f), "../Models/house.png", 3);
	Material* dogMaterial = new Material(glm::vec3(0.f,0.f,0.f), glm::vec3(0.7f, 0.7f, 0.7f), glm::vec3(0.0f, 0.0f, 0.0f), "../Models/dog.jpg", 4);
	Material* treeMaterial = new Material(glm::vec3(0.f,0.f,0.f), glm::vec3(0.7f, 0.7f, 0.7f), glm::vec3(0.0f, 0.0f, 0.0f), "../Models/tree.png", 5);
	//Transformation transformation;
	scene1 = new Scene();
	scene2 = new Scene();
	scene3 = new Scene();
	scene4 = new Scene();
	scene = new Scene();
	Scene * nightScene = new Scene();


	

	scene1->setCamera(camera);
	scene2->setCamera(camera);
	scene3->setCamera(camera);
	scene4->setCamera(camera);
	nightScene->setCamera(camera);
	camera->attach(light1);


	//scene1->addLight(light1);
	//scene1->addLight(light3);
	scene1->addLight(directionLight);
	
	scene2->addLight(light2);
	scene2->addLight(directionLight);
	scene3->addLight(light3);
	scene3->addLight(light1);
	scene2->addLight(light1);
	scene4->addLight(light1);
	nightScene->addLight(light1);
	
	light1->attach(shaderPhong);
	light1->attach(shaderBlinn);
	light1->attach(shaderLambert);
	light1->attach(shaderConstant);
	light1->attach(shaderPhongTexture);
	light2->attach(shaderPhong);
	light2->attach(shaderBlinn);
	light2->attach(shaderLambert);
	light2->attach(shaderConstant);
	light2->attach(shaderPhongTexture);
	light3->attach(shaderPhong);
	light3->attach(shaderBlinn);
	light3->attach(shaderLambert);
	light3->attach(shaderConstant);
	light3->attach(shaderPhongTexture);

	
	
	
	directionLight->attach(shaderPhong);
	directionLight->attach(shaderBlinn);
	directionLight->attach(shaderLambert);
	directionLight->attach(shaderConstant);
	directionLight->attach(shaderPhongTexture);
	//directionLight->attach(shaderHouse);
	
	
	
	scene->addObject(new DrawableObject(triangleModel, shader1,glowingMaterial));

	DrawableObject* drawablePlain = new DrawableObject(plainDenseTextureModel, shaderPhongTexture , grassMaterial);
	Transformation transformationPlain;
	transformationPlain.add(std::make_shared <Translate>(0.f, 0.f, 0.f));
	transformationPlain.add(std::make_shared <Scale>(50.f, 50.f, 50.f));
	drawablePlain->setTransformation(transformationPlain);
	scene1->addObject(drawablePlain);
	nightScene->addObject(drawablePlain);

	DrawableObject* drawableHouse = new DrawableObject(houseModel, shaderPhongTexture, houseMaterial);
	Transformation transformationHouse;
	transformationHouse.add(std::make_shared <Translate>(0.f, 0.f, -25.f));
	transformationHouse.add(std::make_shared <Rotate>(-90.f,0.0, 1.0f, 0.0f));
	drawableHouse->setTransformation(transformationHouse);
	scene1->addObject(drawableHouse);
	nightScene->addObject(drawableHouse);

	DrawableObject* drawableLogin = new DrawableObject(loginModel, shaderPhongTexture, woodMaterial);
	Transformation transformationLogin;
	
	transformationLogin.add(std::make_shared <Translate>(0.f, 15.f, 0.f));
	transformationLogin.add(std::make_shared <DynamicRotate>(1.f, 0.f, 1.f, 0.f));
	transformationLogin.add(std::make_shared <Scale>(2.f, 2.f, 2.f));
	drawableLogin->setTransformation(transformationLogin);
	scene1->addObject(drawableLogin);
	nightScene->addObject(drawableLogin);


	DrawableObject* drawableDog = new DrawableObject(dogModel, shaderPhongTexture, dogMaterial);
	Transformation transformationDog;
	transformationDog.add(std::make_shared <Translate>(-8.f, 0.f, 8.f));
	transformationDog.add(std::make_shared<Rotate>(90, 1.0f, 0.0f, 0.0f));
	transformationDog.add(std::make_shared<Rotate>(180, 0.0f, 1.0f, 0.0f));
	transformationDog.add(std::make_shared<Rotate>(180, 0.0f, 0.0f, 1.0f));
	transformationDog.add(std::make_shared <Scale>(0.08f, 0.08f, 0.08f));
	drawableDog->setTransformation(transformationDog);
	scene1->addObject(drawableDog);
	nightScene->addObject(drawableDog);

	// DrawableObject* drawablePlainTexture = new DrawableObject(plainTextureModel, shaderPhongTexture, woodMaterial);
	// Transformation transformationPlainTexture;
	// transformationPlainTexture.add(std::make_shared <Translate>(0.f, 2.f, 0.f));
	// transformationPlainTexture.add(std::make_shared <Scale>(5.f, 5.f, 5.f));
	// drawablePlainTexture->setTransformation(transformationPlainTexture);
	// scene1->addObject(drawablePlainTexture);
	
	
	scene1->setSkyEnabled(true);
	
	for (int i = 0; i < 100; i++) {
		//std::srand(static_cast<unsigned int>(6646545+i*1000000));
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
		DrawableObject* drawableTree = new DrawableObject(textureTreeModel, shaderPhongTexture, treeMaterial);
		Transformation transformation;

		//auto autoRotate = std::make_shared<DynamicRotate>(1.f,0.f, 1.f, 0.f);
		
		auto translate = std::make_shared<Translate>(x, 0.f, z);
		transformation.add(translate);
		//transformation.add(autoRotate);
		auto rotate = std::make_shared<Rotate>(randAngle, 0.0f, 1.0f, 0.0f);
		transformation.add(rotate);
		auto scale = std::make_shared<Scale>(0.2f * heigth, 0.2f * heigth, 0.2f * heigth);
		transformation.add(scale);
		drawableTree->setTransformation(transformation);
		scene1->addObject(drawableTree);
		nightScene->addObject(drawableTree);
		
		
	}
	for (int i = 0; i < 100; i++) {
		//std::srand(static_cast<unsigned int>(544565465654 + i * 100000));
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
		DrawableObject* drawableBush = new DrawableObject(bushModel, shaderPhong, matteMaterial);
		Transformation transformation;

		auto translate = std::make_shared<Translate>(x, 0.f, z);
		transformation.add(translate);
		auto rotate = std::make_shared<Rotate>(randAngle, 0.0f, 1.0f, 0.0f);
		transformation.add(rotate);
		auto scale = std::make_shared<Scale>(1.f * heigth, 1.f * heigth, 1.f * heigth);
		transformation.add(scale);
		drawableBush->setTransformation(transformation);
		scene1->addObject(drawableBush);
		nightScene->addObject(drawableBush);


	}

	for (int i = 0; i < 10; i++) {
		

		//DrawableObject* drawableSuziSmooth = new DrawableObject(suziSmoothModel, shaderPhong);
		Transformation transformation;
		int upperBound = 20;
		int lowerBound = -20;

		float x = (float)((std::rand() % (upperBound - lowerBound + 1)) + lowerBound);
		float z = (float)((std::rand() % (upperBound - lowerBound + 1)) + lowerBound);
		Light* light = new Light(glm::vec3( x, 0.0f, z), glm::vec4(0.749f, 0.78f, 0.071f, 1.0f),glm::vec3(1.0, 0.018, 0.055));
		DrawableLight* drawableLight = new DrawableLight(sphereModel, shaderDrawableLight, glowingMaterial,light);
		drawableLight->attach(shaderPhong);
		drawableLight->attach(shaderBlinn);
		drawableLight->attach(shaderLambert);
		drawableLight->attach(shaderConstant);
		drawableLight->attach(shaderDrawableLight);
		drawableLight->attach(shaderPhongTexture);
		scene1->addLight(drawableLight);
		nightScene->addLight(drawableLight);
		auto translate = std::make_shared <RandomTranslate>(5.f, x, 0.0f, z);
		translate->setBoundsX(-5.f, 5.f);
		translate->setBoundsY(1.f, 5.f);
		translate->setBoundsZ(-5.f, 5.f);
		transformation.add(translate);
		auto scale = std::make_shared<Scale>(0.04f, 0.04f, 0.04f);
		transformation.add(scale);
		drawableLight->setTransformation(transformation);
		
		scene1->addObject(drawableLight);
		nightScene->addObject(drawableLight);
	}


	
	

	DrawableObject* drawableSphere1 = new DrawableObject(sphereModel, shaderPhong,glowingMaterial);
	Transformation transformation1;
	
	transformation1.add(std::make_shared <Translate>(1.5f, 1.5f, 0.f));
	
	transformation1.add(std::shared_ptr<BezierTranslate>(new BezierTranslate(0.01f, 0.5f, glm::mat4(glm::vec4(-1.0, 3.0, -3.0, 1.0),
		glm::vec4(3.0, -6.0, 3.0, 0),
		glm::vec4(-3.0, 3.0, 0, 0),
		glm::vec4(1, 0, 0, 0)), glm::mat4x3(glm::vec3(-1, 0, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, -1, 0),
		glm::vec3(1, 0, 0)))));
	
	

	
	drawableSphere1->setTransformation(transformation1);
	scene2->addObject(drawableSphere1);

	DrawableObject* drawableSphere2 = new DrawableObject(sphereModel, shaderLambert,shinyMaterial);
	Transformation transformation2;
	transformation2.add(std::make_shared <Translate>(-1.5f, 1.5f, 0.f));
	transformation2.add(std::shared_ptr<BezierTranslate>(new BezierTranslate(0.01f, 0.5f, glm::mat4(glm::vec4(-1.0, 3.0, -3.0, 1.0),
		glm::vec4(3.0, -6.0, 3.0, 0),
		glm::vec4(-3.0, 3.0, 0, 0),
		glm::vec4(1, 0, 0, 0)), glm::mat4x3(glm::vec3(1, 0, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(-1, 0, 0)))));
	drawableSphere2->setTransformation(transformation2);
	
	scene2->addObject(drawableSphere2);
	

	DrawableObject* drawableSphere3 = new DrawableObject(sphereModel, shaderBlinn,matteMaterial);
	Transformation transformation3;
	transformation3.add(std:: make_shared<DynamicRotate>(2, 1.0f, 0.0f, -1.0f));
	transformation3.add(std::make_shared <Translate>(1.5f, -1.5f, 0.f));
	transformation3.add(std::shared_ptr<BezierTranslate>(new BezierTranslate(0.01f, 0.5f, glm::mat4(glm::vec4(-1.0, 3.0, -3.0, 1.0),
		glm::vec4(3.0, -6.0, 3.0, 0),
		glm::vec4(-3.0, 3.0, 0, 0),
		glm::vec4(1, 0, 0, 0)), glm::mat4x3(glm::vec3(-1, 0, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, -1, 0),
		glm::vec3(1, 0, 0)))));
	
	drawableSphere3->setTransformation(transformation3);
	scene2->addObject(drawableSphere3);

	DrawableObject* drawableSphere4 = new DrawableObject(sphereModel, shaderPhong,glowingMaterial);
	Transformation transformation4;
	transformation4.add(std::make_shared <Translate>(-1.5f, -1.5f, 0.f));
	transformation4.add(std::shared_ptr<BezierTranslate>(new BezierTranslate(0.01f, 0.5f, glm::mat4(glm::vec4(-1.0, 3.0, -3.0, 1.0),
		glm::vec4(3.0, -6.0, 3.0, 0),
		glm::vec4(-3.0, 3.0, 0, 0),
		glm::vec4(1, 0, 0, 0)), glm::mat4x3(glm::vec3(1, 0, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(-1, 0, 0)))));
	drawableSphere4->setTransformation(transformation4);
	scene2->addObject(drawableSphere4);

	

	DrawableObject* drawableGift = new DrawableObject(giftModel, shaderPhong,glowingMaterial);
	DrawableObject* drawableSuziSmooth = new DrawableObject(suziSmoothModel, shaderBlinn,glowingMaterial);
	DrawableObject* drawableTree = new DrawableObject(treeModel, shaderLambert,glowingMaterial);
	DrawableObject* drawableSphere = new DrawableObject(sphereModel, shaderPhong,glowingMaterial);
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
	DrawableObject* drawableTreeRotate = new DrawableObject(treeModel, shaderBlinn,glowingMaterial);
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
	nightScene->cameraInit();



	
	sceneController->addScene(scene);
	sceneController->addScene(scene1);
	sceneController->addScene(nightScene);
	sceneController->addScene(scene2);
	sceneController->addScene(scene3);
	sceneController->addScene(scene4);
	
	
	
	
	
	



	
	
	
}

void App::run()
{
	bool fKeyPressed = false;
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window)) {
		//clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
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
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
			if (!fKeyPressed) {
				sceneController->freezSkyBox();
				fKeyPressed = true; 
			}
		} else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE) {
			fKeyPressed = false; 
		}
		if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE){
			lockMouse = true;
		}
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
			lockMouse = false;
		}
		
		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
			sceneController->switchScene(0);
		}
		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
			sceneController->switchScene(1);
		}
		if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
			sceneController->switchScene(2);
		}
		if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
			sceneController->switchScene(3);
		}
		if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
			sceneController->switchScene(4);
		}
		if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
			sceneController->switchScene(5);
		}

		sceneController->render();
		
		
		// update other events like input handling
		glfwPollEvents();
		// put the stuff we�ve been drawing onto the display
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}
