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
shared_ptr<Shape> shape;

int g_width, g_height;
bool anime, up;
float sTheta, xmove, shoulder;

static void error_callback(int error, const char *description)
{
	cerr << description << endl;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	else if(key == GLFW_KEY_A && action == GLFW_PRESS) {
		xmove -= 0.1;
	}
	else if(key == GLFW_KEY_D && action == GLFW_PRESS) {
		xmove += 0.1;
	}
	else if(key == GLFW_KEY_X && action == GLFW_PRESS) {
		if (anime)
         anime = false;
      else
         anime = true;
	}
   else if(key == GLFW_KEY_C && action == GLFW_PRESS) {
      shoulder += 0.05;
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
   xmove = 0;
   anime = false;
   up = true;

	// Set background color.
	glClearColor(.12f, .34f, .56f, 1.0f);
	// Enable z-buffer test.
	glEnable(GL_DEPTH_TEST);

	// Initialize mesh.
	shape = make_shared<Shape>();
	shape->loadMesh(RESOURCE_DIR + "cube.obj");
	shape->resize();
	shape->init();

	// Initialize the GLSL program.
	prog = make_shared<Program>();
	prog->setVerbose(true);
	prog->setShaderNames(RESOURCE_DIR + "simple_vert.glsl", RESOURCE_DIR + "simple_frag.glsl");
	prog->init();
	prog->addUniform("P");
	prog->addUniform("MV");
	prog->addAttribute("vertPos");
	prog->addAttribute("vertNor");
}

static void render()
{
   float wave = 0;
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
	prog->bind();
	glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, value_ptr(P->topMatrix()));

	/* draw bottom cube */	
   MV->loadIdentity();
   MV->translate(vec3(xmove, 0, 0));
   MV->pushMatrix();
	  //draw the bottom cube - chest
		MV->translate(vec3(0, 0, -5));
	  	MV->scale(vec3(0.75, 0.75, 0.75));
	  	glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, value_ptr(MV->topMatrix()));
	  	shape->draw(prog);

		//right arm
     	MV->pushMatrix();
		//place at shoulder
		MV->translate(vec3(1, 0.9, 0));
		//rotate shoulder joint
	   MV->rotate(-0.5+0.15*sTheta, vec3(0, 0, 1));
		//move to shoulder joint
		MV->translate(vec3(0.75, 0, 0));
		   //right lower arm
		   MV->pushMatrix();
         MV->translate(vec3(0.6, 0, 0));
         MV->rotate(sTheta, vec3(0, 0, 1));
         MV->translate(vec3(1, 0, 0));
            //right hand
            MV->pushMatrix();
            MV->translate(vec3(0.75, 0, 0));
            MV->scale(vec3(0.35, 0.35, 0.25));
            glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, value_ptr(MV->topMatrix()));
            shape->draw(prog);
            MV->popMatrix();
         MV->scale(vec3(0.85, 0.25, 0.25));
         glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, value_ptr(MV->topMatrix()));
         shape->draw(prog);
         MV->popMatrix();
		//non-uniform scale
	  	MV->scale(vec3(0.85, 0.25, 0.25));
	  	glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, value_ptr(MV->topMatrix()));
	  	shape->draw(prog);
   	MV->popMatrix();
      
      //left arm
     	MV->pushMatrix();
		//place at shoulder
		MV->translate(vec3(-1, 0.9, 0));
		//rotate shoulder joint
	   MV->rotate(1.3+shoulder, vec3(0, 0, 1));
		//move to shoulder joint
		MV->translate(vec3(-0.75, 0, 0));
		   //left lower arm
		   MV->pushMatrix();
         MV->translate(vec3(-0.6, 0, 0));
         MV->rotate(0.2, vec3(0, 0, 1));
         MV->translate(vec3(-1, 0, 0));
            //left hand
            MV->pushMatrix();
            MV->translate(vec3(-0.75, 0, 0));
            MV->scale(vec3(0.35, 0.35, 0.25));
            glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, value_ptr(MV->topMatrix()));
            shape->draw(prog);
            MV->popMatrix();
         MV->scale(vec3(0.85, 0.25, 0.25));
         glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, value_ptr(MV->topMatrix()));
         shape->draw(prog);
         MV->popMatrix();
		//non-uniform scale
	  	MV->scale(vec3(0.85, 0.25, 0.25));
	  	glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, value_ptr(MV->topMatrix()));
	  	shape->draw(prog);
   	MV->popMatrix();

   MV->popMatrix();
   
	/* draw top cube - aka head */	
   MV->loadIdentity();
   MV->translate(vec3(xmove, 0, 0));
	MV->pushMatrix();
	  /*play with these options */
	  MV->translate(vec3(0, 1.1, -5));
	  MV->rotate(0.5, vec3(0, 1, 0));
	  MV->scale(vec3(0.5, 0.5, 0.5));
	  	glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, value_ptr(MV->topMatrix()));
	  shape->draw(prog);
   MV->popMatrix();

	prog->unbind();

   // Pop matrix stacks.
   P->popMatrix();

	/* update shoulder angle - animate */
	if (anime && sTheta < 1.2) {
		sTheta += 0.01;
	}
   else {
      if (anime && up) {
         sTheta += 0.01;
         if (sTheta > 1.9) {
            up = false;
         }
      }
      if (anime && !up) {
         sTheta -= 0.01;
         if (sTheta < 1.2)
            up = true;
      }
   }
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
