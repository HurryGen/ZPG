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
	glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetMouseButtonCallback(window, button_callback);
	glfwSetWindowFocusCallback(window, window_focus_callback);
	glfwSetWindowIconifyCallback(window, window_iconify_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);

	
	



}

void App::createShaders()
{
	shader = new Shader(vertex_shader2, fragment_shader2);
	shader1 = new Shader(vertex_shader, fragment_shader);

}

void App::createModels()
{
	treeModel = new Model(tree, sizeof(tree)/sizeof(tree[0]), GL_TRIANGLES, 0, sizeof(bushes));
	bushModel = new Model(bushes, sizeof(bushes) / sizeof(bushes[0]), GL_TRIANGLES, 0, sizeof(bushes));
	giftModel = new Model(gift, sizeof(gift) / sizeof(gift[0]), GL_TRIANGLES, 0, sizeof(gift));
}

void App::createScenes()
{
	//Transformation transformation;
	scene1 = new Scene();
	scene2 = new Scene();

	/*scene1->addobject(new drawableobject(treemodel, shader));
	transformation.scale(0.2f, 0.2f, 0.2f);
	transformation.translate(-0.7f,-0.7f, 0.f);
	scene1->getObjects().at(0)->setTransformation(transformation);
	scene1->addObject(new DrawableObject(treeModel, shader));
	transformation.reset();
	transformation.scale(0.2f, 0.2f, 0.2f);
	transformation.translate(0.7f, -0.7f, 0.f);
	transformation.rotate(90.f, 0.3f, 1.f, 0.f);
	scene1->getObjects().at(1)->setTransformation(transformation);
	scene1->addObject(new DrawableObject(bushModel, shader));
	transformation.reset();
	transformation.scale(1.f, 1.f, 1.f);
	transformation.translate(0.f, -1.f, 0.f);
	scene1->getObjects().at(2)->setTransformation(transformation);
	scene1->addObject(new DrawableObject(giftModel, shader));
	transformation.reset();
	transformation.rotate(180.f, 0.f, 1.f, 0.f);
	scene1->getObjects().at(3)->setTransformation(transformation);

	scene2->addObject(new DrawableObject(treeModel, shader));*/
	
	for (int i = 0; i < 100; i++) {
		std::srand(static_cast<unsigned int>(16161616+i*565));
		int lowerBound = -360;
		int upperBound = 360;
		float randAngle = (std::rand() % (upperBound - lowerBound + 1)) + lowerBound;
		float x = (float)((std::rand() % (upperBound - lowerBound + 1)) + lowerBound)/100;
		float y = (float)((std::rand() % (upperBound - lowerBound + 1)) + lowerBound) / 100;
		float z = (float)((std::rand() % (upperBound - lowerBound + 1)) + lowerBound) / 100;
		DrawableObject* drawableTree = new DrawableObject(treeModel, shader);
		Transformation transformation;
		transformation.scale(0.2f, 0.2f, 0.2f);
		transformation.rotate(randAngle,0.0f, 1.0f, 0.0f);
		transformation.translate(x,y,z);
		drawableTree->setTransformation(transformation);
		scene1->addObject(drawableTree);
		
		
	}
	for (int i = 0; i < 100; i++) {
		std::srand(static_cast<unsigned int>(16161616 + i * 725));
		int lowerBound = -360;
		int upperBound = 360;
		float randAngle = (std::rand() % (upperBound - lowerBound + 1)) + lowerBound;
		float x = (float)((std::rand() % (upperBound - lowerBound + 1)) + lowerBound) / 100;
		float y = (float)((std::rand() % (upperBound - lowerBound + 1)) + lowerBound) / 100;
		float z = (float)((std::rand() % (upperBound - lowerBound + 1)) + lowerBound) / 100;
		DrawableObject* drawableBush = new DrawableObject(bushModel, shader);
		Transformation transformation;
		transformation.scale(0.2f, 0.2f, 0.2f);
		transformation.rotate(randAngle, 0.0f, 1.0f, 0.0f);
		transformation.translate(x, y, z);
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
