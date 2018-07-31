/* Lab 6 base code - transforms using matrix stack built on glm 
	CPE 471 Cal Poly Z. Wood + S. Sueda
*/
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GLSL.h"
#include "Program.h"
#include "MatrixStack.h"
#include "Shape.h"

// value_ptr for glm
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;

/* to use glee */
#define GLEE_OVERWRITE_GL_FUNCTIONS
#include "glee.hpp"

GLFWwindow *window; // Main application window
string RESOURCE_DIR = ""; // Where the resources are loaded from
shared_ptr<Program> prog;
shared_ptr<Program> prog2;
shared_ptr<Program> prog3;
shared_ptr<Program> prog4;
shared_ptr<Shape> shape;

int g_width, g_height;
float sTheta;
bool press;

static void error_callback(int error, const char *description)
{
	cerr << description << endl;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	else if(key == GLFW_KEY_T && action == GLFW_PRESS) {
		if (!press) {
         press = true;
      }
      else {
         press = false;
      }
	}
}


static void mouse_callback(GLFWwindow *window, int button, int action, int mods)
{
   double posX, posY;
   if (action == GLFW_PRESS) {
      glfwGetCursorPos(window, &posX, &posY);
      cout << "Pos X " << posX <<  " Pos Y " << posY << endl;
	}
}

static void resize_callback(GLFWwindow *window, int width, int height) {
   g_width = width;
   g_height = height;
   glViewport(0, 0, width, height);
}


static void init()
{
	GLSL::checkVersion();

	sTheta = 0;
   press = false;
	// Set background color.
	glClearColor(.12f, .34f, .56f, 1.0f);
	// Enable z-buffer test.
	glEnable(GL_DEPTH_TEST);

	// Initialize mesh.
	shape = make_shared<Shape>();
	shape->loadMesh(RESOURCE_DIR + "sphere.obj");
	shape->resize();
	shape->init();

	// Initialize the GLSL program.
	prog = make_shared<Program>();
	prog->setVerbose(true);
	prog->setShaderNames(RESOURCE_DIR + "simple_vert.glsl", RESOURCE_DIR + "simple_frag.glsl");
	prog->init();
   prog->addUniform("kd");
   prog->addUniform("ka");
   prog->addUniform("IL");
   prog->addUniform("light");
	prog->addUniform("P");
	prog->addUniform("MV");
	prog->addAttribute("vertPos");
	prog->addAttribute("vertNor");

	prog2 = make_shared<Program>();
	prog2->setVerbose(true);
	prog2->setShaderNames(RESOURCE_DIR + "vert2.glsl", RESOURCE_DIR + "simple_frag.glsl");
	prog2->init();
   prog2->addUniform("kd");
   prog2->addUniform("ka");
   prog2->addUniform("IL");
   prog2->addUniform("light");
	prog2->addUniform("P");
	prog2->addUniform("MV");
	prog2->addAttribute("vertPos");
	prog2->addAttribute("vertNor");

	prog3 = make_shared<Program>();
	prog3->setVerbose(true);
	prog3->setShaderNames(RESOURCE_DIR + "phongvert.glsl", RESOURCE_DIR + "phongfrag.glsl");
	prog3->init();
   prog3->addUniform("kd");
   prog3->addUniform("ka");
   prog3->addUniform("IL");
   prog3->addUniform("light");
	prog3->addUniform("P");
	prog3->addUniform("MV");
	prog3->addAttribute("vertPos");
	prog3->addAttribute("vertNor");

	prog4 = make_shared<Program>();
	prog4->setVerbose(true);
	prog4->setShaderNames(RESOURCE_DIR + "phongvert2.glsl", RESOURCE_DIR + "phongfrag.glsl");
	prog4->init();
   prog4->addUniform("kd");
   prog4->addUniform("ka");
   prog4->addUniform("IL");
   prog4->addUniform("light");
	prog4->addUniform("P");
	prog4->addUniform("MV");
	prog4->addAttribute("vertPos");
	prog4->addAttribute("vertNor");
}

static void render()
{
	// Get current frame buffer size.
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	// Clear framebuffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Use the matrix stack for Lab 6
   float aspect = width/(float)height;

   // Create the matrix stacks - please leave these alone for now
   auto P = make_shared<MatrixStack>();
   auto MV = make_shared<MatrixStack>();
   // Apply perspective projection.
   P->pushMatrix();
   P->perspective(45.0f, aspect, 0.01f, 100.0f);

	// Draw a stack of cubes with indiviudal transforms 
	if (!press) {
	   prog->bind();
	   glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, value_ptr(P->topMatrix()));
	   glUniform3f(prog->getUniform("light"), -1, 3, 0);
	   glUniform3f(prog->getUniform("kd"), 0.5, 0, 1);
	   glUniform3f(prog->getUniform("ka"), 0.4, 0.4, 0.4);
	   glUniform3f(prog->getUniform("IL"), 1, 1, 1);
	   /* draw spheres */	
	   MV->pushMatrix();
         MV->loadIdentity();
	      MV->translate(vec3(0, 0.1, -5));
	      MV->rotate(sTheta, vec3(0, 1, 0));
         MV->translate(vec3(1.5, 0, 0));
	      MV->scale(vec3(0.8, 0.8, 0.8));
	  	   glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, value_ptr(MV->topMatrix()));
	      shape->draw(prog);
      MV->popMatrix();
	   prog->unbind();

	   prog2->bind();
	   glUniformMatrix4fv(prog2->getUniform("P"), 1, GL_FALSE, value_ptr(P->topMatrix()));
	   glUniform3f(prog2->getUniform("light"), -1, 3, 0);
	   glUniform3f(prog2->getUniform("kd"), 0, 0.7, 0);
	   glUniform3f(prog2->getUniform("ka"), 0.4, 0.4, 0.4);
	   glUniform3f(prog2->getUniform("IL"), 1, 1, 1);
   
   	MV->pushMatrix();
         MV->loadIdentity();
	      MV->translate(vec3(0, 0.1, -5));
	      MV->rotate(sTheta, vec3(0, 1, 0));
         MV->translate(vec3(-1.5, 0, 0));
	      MV->scale(vec3(0.8, 0.8, 0.8));
	  	   glUniformMatrix4fv(prog2->getUniform("MV"), 1, GL_FALSE, value_ptr(MV->topMatrix()));
	      shape->draw(prog2);
      MV->popMatrix();
	   prog2->unbind();
   }
   else {
	   prog3->bind();
	   glUniformMatrix4fv(prog3->getUniform("P"), 1, GL_FALSE, value_ptr(P->topMatrix()));
	   glUniform3f(prog3->getUniform("light"), -1, 3, 0);
	   glUniform3f(prog3->getUniform("kd"), 0.5, 0, 1);
	   glUniform3f(prog3->getUniform("ka"), 0.4, 0.4, 0.4);
	   glUniform3f(prog3->getUniform("IL"), 1, 1, 1);
	   /* draw spheres */	
	   MV->pushMatrix();
         MV->loadIdentity();
	      MV->translate(vec3(0, 0.1, -5));
	      MV->rotate(sTheta, vec3(0, 1, 0));
         MV->translate(vec3(1.5, 0, 0));
	      MV->scale(vec3(0.8, 0.8, 0.8));
	  	   glUniformMatrix4fv(prog3->getUniform("MV"), 1, GL_FALSE, value_ptr(MV->topMatrix()));
	      shape->draw(prog3);
      MV->popMatrix();
	   prog3->unbind();

	   prog4->bind();
	   glUniformMatrix4fv(prog4->getUniform("P"), 1, GL_FALSE, value_ptr(P->topMatrix()));
	   glUniform3f(prog4->getUniform("light"), -1, 3, 0);
	   glUniform3f(prog4->getUniform("kd"), 0, 0.7, 0);
	   glUniform3f(prog4->getUniform("ka"), 0.4, 0.4, 0.4);
	   glUniform3f(prog4->getUniform("IL"), 1, 1, 1);
  
   	MV->pushMatrix();
         MV->loadIdentity();
	      MV->translate(vec3(0, 0.1, -5));
	      MV->rotate(sTheta, vec3(0, 1, 0));
         MV->translate(vec3(-1.5, 0, 0));
	      MV->scale(vec3(0.8, 0.8, 0.8));
	  	   glUniformMatrix4fv(prog4->getUniform("MV"), 1, GL_FALSE, value_ptr(MV->topMatrix()));
	      shape->draw(prog4);
      MV->popMatrix();
	   prog4->unbind();
   }

   // Pop matrix stacks.
   P->popMatrix();

   sTheta += 0.02;
}

int main(int argc, char **argv)
{
	if(argc < 2) {
		cout << "Please specify the resource directory." << endl;
		return 0;
	}
	RESOURCE_DIR = argv[1] + string("/");

	// Set error callback.
	glfwSetErrorCallback(error_callback);
	// Initialize the library.
	if(!glfwInit()) {
		return -1;
	}
   //request the highest possible version of OGL - important for mac
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

	// Create a windowed mode window and its OpenGL context.
	window = glfwCreateWindow(640, 480, "YOUR NAME", NULL, NULL);
	if(!window) {
		glfwTerminate();
		return -1;
	}
	// Make the window's context current.
	glfwMakeContextCurrent(window);
	// Initialize GLEW.
	glewExperimental = true;
	if(glewInit() != GLEW_OK) {
		cerr << "Failed to initialize GLEW" << endl;
		return -1;
	}
	//weird bootstrap of glGetError
   glGetError();
	cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
   cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

	// Set vsync.
	glfwSwapInterval(1);
	// Set keyboard callback.
	glfwSetKeyCallback(window, key_callback);
   //set the mouse call back
   glfwSetMouseButtonCallback(window, mouse_callback);
   //set the window resize call back
   glfwSetFramebufferSizeCallback(window, resize_callback);

	// Initialize scene. Note geometry initialized in init now
	init();

	// Loop until the user closes the window.
	while(!glfwWindowShouldClose(window)) {
		// Render scene.
		render();
		// Swap front and back buffers.
		glfwSwapBuffers(window);
		// Poll for and process events.
		glfwPollEvents();
	}
	// Quit program.
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
