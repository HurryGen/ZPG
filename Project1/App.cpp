#include "App.h"
#include "../Models/tree.h"
#include "../Models/bushes.h"
#include "../Models/gift.h"







const char* vertex_shader =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"uniform mat4 modelMatrix;"
"void main () {"
"     gl_Position = modelMatrix * vec4 (vp, 1.0);"
"}";


const char* vertex_shader2 =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec4 vn;"
"uniform mat4 modelMatrix;"
"uniform mat4 viewMatrix;"
"uniform mat4 projectionMatrix;"
"out vec4 color;"
"void main () {"
"     gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (vp, 1.0);"
"     color = vn;"
"}";

const char* vertex_shader3 =
"#version 330\n"
"layout(location = 0) in vec3 vp;"
"layout(location = 1) in vec3 vn;"
"uniform mat4 modelMatrix;"
"uniform mat4 viewMatrix;"
"uniform mat4 projectionMatrix;"
"out vec3 fragNormal;"
"out vec3 fragPosition;"
"void main() {"
	"gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (vp, 1.0);"
	"fragNormal = mat3(transpose(inverse(model))) * vn;"
	"fragPosition = vec3(model * vec4(vp, 1.0));"
" }";



const char* fragment_shader =
"#version 330\n"
"out vec4 frag_colour;"
"void main () {"
"     frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
"}";

const char* fragment_shader2 =
"#version 330\n"
"in vec4 color;"
"out vec4 frag_colour;"
"void main () {"
"     frag_colour = color;"	
"}";


const char* fragment_shader3 =
"#version 400\n"
"in vec3 fragPosition;"
"in vec3 fragNormal;"
"out vec4 fragColor;"
"const vec3 lightPos = vec3(0.0, 0.0, 0.0);"
"const vec4 lightColor = vec4(0.3, 0.3, 1.0, 1.0);"
"const vec4 ambient = vec4(0.25, 0.25, 0.25, 1.0);"
"const float specularStrength = 15.0;"
"const vec3 viewDir = vec3(0.0, 0.0, 0.0);"
"void main(void)"
"{"
	"vec3 normal = normalize(fragNormal);"
	"vec3 lightDir = normalize(lightPos - fragPosition);"
	"float diffIntensity = max(dot(normal, lightDir), 0.0);"
	"vec3 reflectDir = reflect(-lightDir, normal);"
	"float spec = pow(max(dot(normalize(viewDir), reflectDir), 0.0), 32.0);"
	"vec4 objectColor = vec4(0.8, 0.8, 0.8, 1.0);"
	"vec4 diffuseColor = diffIntensity * lightColor;"
	"vec4 specularColor = specularStrength * spec * lightColor;"
	"fragColor = ambient + (diffuseColor + specularColor) * objectColor;"
"}";


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
	shader = new Shader(vertex_shader2, fragment_shader2);
	shader1 = new Shader(vertex_shader, fragment_shader);
	shaderWithLight = new Shader(vertex_shader3, fragment_shader3);
	camera->attach(shader);
	camera->attach(shaderWithLight);

}

void App::createModels()
{
	treeModel = new Model(tree, sizeof(tree)/sizeof(tree[0]), GL_TRIANGLES, 0, sizeof(bushes));
	bushModel = new Model(bushes, sizeof(bushes) / sizeof(bushes[0]), GL_TRIANGLES, 0, sizeof(bushes));
	giftModel = new Model(gift, sizeof(gift) / sizeof(gift[0]), GL_TRIANGLES, 0, sizeof(gift));
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

	

	scene2->addObject(new DrawableObject(treeModel, shader));
	
	for (int i = 0; i < 100; i++) {
		//std::srand(static_cast<unsigned int>(6646545+i*1000000));
		int lowerBoundAngle = -360;
		int upperBoundAngle = 360;
		int upperBound = 10;
		int lowerBound = -10;
		int upperBoundHeigth = 100;
		int lowerBoundHeigth = 10;
		float randAngle = (std::rand() % (upperBoundAngle - lowerBoundAngle + 1)) + lowerBoundAngle;
		float heigth = (float)((std::rand() % (upperBoundHeigth - lowerBoundHeigth + 1)) + lowerBoundHeigth)/100;
		float x = (float)((std::rand() % (upperBound - lowerBound + 1)) + lowerBound);
		float z = (float)((std::rand() % (upperBound - lowerBound + 1)) + lowerBound);
		DrawableObject* drawableTree = new DrawableObject(treeModel, shader);
		Transformation transformation;
		transformation.scale(0.5f * heigth, 0.5f * heigth, 0.5f * heigth);
		transformation.rotate(randAngle,0.0f, 1.0f, 0.0f);
		transformation.translate(x, 0.f,z);
		drawableTree->setTransformation(transformation);
		scene1->addObject(drawableTree);
		
		
	}
	for (int i = 0; i < 100; i++) {
		//std::srand(static_cast<unsigned int>(544565465654 + i * 100000));
		int lowerBoundAngle = -360;
		int upperBoundAngle = 360;
		int upperBound = 10;
		int lowerBound = -10;
		int upperBoundHeigth = 300;
		int lowerBoundHeigth = 10;
		float randAngle = (std::rand() % (upperBoundAngle - lowerBoundAngle + 1)) + lowerBoundAngle;
		float heigth = (float)((std::rand() % (upperBoundHeigth - lowerBoundHeigth + 1)) + lowerBoundHeigth) / 100;
		float x = (float)((std::rand() % (upperBound - lowerBound + 1)) + lowerBound);
		float z = (float)((std::rand() % (upperBound - lowerBound + 1)) + lowerBound);
		DrawableObject* drawableBush = new DrawableObject(bushModel, shader);
		Transformation transformation;
		//transformation.scale(0.2f, 0.2f, 0.2f);
		transformation.scale(1.f * heigth, 1.f * heigth, 1.f * heigth);
		transformation.rotate(randAngle, 0.0f, 1.0f, 0.0f);
		transformation.translate(x, 0.f, z);
		drawableBush->setTransformation(transformation);
		scene1->addObject(drawableBush);


	}
	
}

void App::run()
{
	
	
	Transformation transformationScene2;
	transformationScene2.scale(0.2f, 0.2f, 0.2f);
	transformationScene2.translate(0.f, -0.7f, 0.f);
	float angle = 1.f;
	int sceneIndex = 0;
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window)) {
		// clear color and depth buffer
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
			scene1->render();
		}
		else if (sceneIndex == 1) {
			scene2->render();
			scene2->getObjects().at(0)->setTransformation(transformationScene2);
			transformationScene2.rotate(angle, 0.f, 1.f, 0.f);
			
		}
		else if (sceneIndex > 1) {
			sceneIndex = 1;
		}
		else if (sceneIndex < 0) {
			sceneIndex = 0;
		}
		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
			sceneIndex = 0;
		}
		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
			sceneIndex = 1;
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
