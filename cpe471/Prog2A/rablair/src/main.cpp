/*
ZJ Wood CPE 471 Lab 3 base code - includes use of glee
https://github.com/nshkurkin/glee
*/

#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GLSL.h"
#include "Program.h"
#include "MatrixStack.h"

// value_ptr for glm
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

/* to use glee */
#define GLEE_OVERWRITE_GL_FUNCTIONS
#include "glee.hpp"

using namespace std;
using namespace glm;

int pixW, pixH;

GLFWwindow *window; // Main application window
string RESOURCE_DIR = ""; // Where the resources are loaded from
shared_ptr<Program> prog; //our shader program
shared_ptr<Program> bkgd; //background shader program

/* Global data associated with triangle geometry - this will likely vary
   in later programs - so is left explicit for now  */
GLuint VertexArrayID;
GLuint VertexArrayIDbkgd;

//data necessary to give our triangle data to OGL
GLuint vertexbuffer; 
GLuint vertexbufferbkgd;

static float p2wX(int xp) {
   int width, height;
   float left, right, c, d, x;

   glfwGetWindowSize(window, &width, &height);
   x = (float)xp;

   if (width > height) {
      left = -width/(float)height;
      right = width/(float)height;
   }
   else {
      left = -1.0;
      right = 1.0;
   }

   d = left;
   c = (right-left)/(width-1.0);

   return (c * x + d);
}

static float p2wY(int yp) {
   int width, height;
   float bot, top, e, f, y;

   glfwGetWindowSize(window, &width, &height);

   y = (float)(height - (float)yp);
   
   if (width > height) {
      bot = -1.0;
      top = 1.0;
   }
   else {
      bot = -height/(float)width;
      top = height/(float)width;
   }
   
   f = bot;
   e = (top-bot)/(height-1.0);

   return (e * y + f);
}

static void error_callback(int error, const char *description)
{
	cerr << description << endl;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

//callback for the mouse when clicked move the triangle when helper functions
//written
static void mouse_callback(GLFWwindow *window, int button, int action, int mods)
{
	double posX, posY;
	float newPt[2];
	if (action == GLFW_PRESS) {
		glfwGetCursorPos(window, &posX, &posY);	
		cout << "Pos X " << posX <<  " Pos Y " << posY << endl;
		//change this to be the points converted to WORLD
		//THIS IS BROKEN< YOU GET TO FIX IT - yay!
		newPt[0] = p2wX(posX);
		newPt[1] = p2wY(posY);
		cout << "converted:" << newPt[0] << " " << newPt[1] << endl;
		//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		//update the vertex array with the updated points
		//glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*6, sizeof(float)*2, newPt);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

//if the window is resized, capture the new size and reset the viewport
static void resize_callback(GLFWwindow *window, int in_width, int in_height) {
	//get the window size - may be different then pixels for retina	
   int width, height;
   glfwGetFramebufferSize(window, &width, &height);
   glViewport(0, 0, width, height);
}

/*Note that any gl calls must always happen after a GL state is initialized */
static void initGeom() {

   GLuint indexbuffer;
   GLuint indexbufferbkgd;

   GLfloat g_vertex_buffer_data[243];
   g_vertex_buffer_data[0] = 0.0;
   g_vertex_buffer_data[1] = 0.0;
   g_vertex_buffer_data[2] = 0.0;

   float r = 0.7;
   float z = 1.0;
   for (int i = 1; i < 81; i++) {
      double angle = (i/80.0)*(2*M_PI);
      if (i%2 == 1) {
         r = 0.5;
         z = -1.0;
      }
      else {
         r = 0.7;
         z = 1.0;
      }

      float x = r*cos(angle);
      float y = r*sin(angle);

      g_vertex_buffer_data[i*3] = x;
      g_vertex_buffer_data[i*3+1] = y;
      g_vertex_buffer_data[i*3+2] = z;
   }

	//generate the VAO
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	//generate vertex buffer to hand off to OGL
	glGenBuffers(1, &vertexbuffer);
	//set the current state to focus on our vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//actually memcopy the data - only do this once
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_DYNAMIC_DRAW);
	
	//we need to set up the vertex array
	glEnableVertexAttribArray(0);
	//key function to get up how many elements to pull out at a time (3)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
	
   // program index data
   GLint index_buffer_data[243];
   for (int i = 0; i < 81; i++) {
      index_buffer_data[i*3] = 0;
      index_buffer_data[i*3+1] = i;
      index_buffer_data[i*3+2] = i+1;
      if (i+1 > 80)
         index_buffer_data[i*3+2] = 1;
   }

   glGenBuffers(1, &indexbuffer);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_buffer_data), index_buffer_data, GL_STATIC_DRAW);

   // background vertex data
   static const GLfloat bkgd_vertex[] = {
      -3.0f, -3.0f, -2.0f,
      3.0f, -3.0f, -2.0f, 
      3.0f, 3.0f, -2.0f,
      -3.0f, 3.0f, -2.0f
   };

   glGenVertexArrays(1, &VertexArrayIDbkgd);
   glBindVertexArray(VertexArrayIDbkgd);
   glGenBuffers(1, &vertexbufferbkgd);
   glBindBuffer(GL_ARRAY_BUFFER, vertexbufferbkgd);
   glBufferData(GL_ARRAY_BUFFER, sizeof(bkgd_vertex), bkgd_vertex, GL_DYNAMIC_DRAW);

   glEnableVertexAttribArray(0);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

   //background index data
   static const GLint bkgd_index[] = {
      0, 1, 2,
      0, 2, 3
   };

   glGenBuffers(1, &indexbufferbkgd);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbufferbkgd);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bkgd_index), bkgd_index, GL_STATIC_DRAW);

   glBindVertexArray(0);
}

//General OGL initialization - set OGL state here
static void init()
{
	GLSL::checkVersion();

	// Set background color.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Enable z-buffer test.
	glEnable(GL_DEPTH_TEST);

	// Initialize the GLSL program.
	prog = make_shared<Program>();
	prog->setVerbose(true);
	prog->setShaderNames(RESOURCE_DIR + "sunvert.glsl", RESOURCE_DIR + "sunfrag.glsl");
	prog->init();
   prog->addUniform("v");
   prog->addUniform("center");
   prog->addUniform("t");
	prog->addUniform("P");
	prog->addUniform("MV");
	prog->addAttribute("vertPos");

   // Initialize the background program
   bkgd = make_shared<Program>();
   bkgd->setVerbose(true);
   bkgd->setShaderNames(RESOURCE_DIR + "bkgdvert.glsl", RESOURCE_DIR + "bkgdfrag.glsl");
   bkgd->init();
   bkgd->addUniform("center");
   bkgd->addUniform("P");
   bkgd->addUniform("MV");
   bkgd->addAttribute("vertPos");
}


/****DRAW
This is the most important function in your program - this is where you
will actually issue the commands to draw any geometry you have set up to
draw
********/
static void render()
{
	// Get current frame buffer size.
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float aspect = width/(float)height;
	glViewport(0, 0, width, height);

   float centerX = width/2.0;
   float centerY = height/2.0;

	// Clear framebuffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Create the matrix stacks - please leave these alone for now
	auto P = make_shared<MatrixStack>();
	auto MV = make_shared<MatrixStack>();
	// Apply orthographic projection.
	P->pushMatrix();
	if (width > height) {
		P->ortho(-1*aspect, 1*aspect, -1, 1, -2, 100.0f);
	} else {
		P->ortho(-1, 1, -1*1/aspect, 1*1/aspect, -2, 100.0f);
	}
	MV->pushMatrix();

   bkgd->bind();
	glUniform2f(bkgd->getUniform("center"), centerX, centerY);
	glUniformMatrix4fv(bkgd->getUniform("P"), 1, GL_FALSE, value_ptr(P->topMatrix()));
	glUniformMatrix4fv(bkgd->getUniform("MV"), 1, GL_FALSE, value_ptr(MV->topMatrix()));

   glBindVertexArray(VertexArrayIDbkgd);

   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
   glBindVertexArray(0);
   bkgd->unbind();

	// Draw the triangle using GLSL.
	prog->bind();

	//send the matrices to the shaders
	glUniform2f(prog->getUniform("v"), 0.3, 0.3);
	glUniform2f(prog->getUniform("center"), centerX, centerY);
	glUniform1f(prog->getUniform("t"), sin(glfwGetTime()));
	glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, value_ptr(P->topMatrix()));
	glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, value_ptr(MV->topMatrix()));

   glBindVertexArray(VertexArrayID);

	//actually draw from vertex 0, 9 vertices
	//glDrawArrays(GL_TRIANGLES, 0, 9);

   glDrawElements(GL_TRIANGLES, 243, GL_UNSIGNED_INT, 0);

   glBindVertexArray(0);
	
	prog->unbind();

	// Pop matrix stacks.
	MV->popMatrix();
	P->popMatrix();
}

int main(int argc, char **argv)
{
   if(argc < 2) {
      cout << "Please specify the resource directory." << endl;
      return 0;
   }
   RESOURCE_DIR = argv[1] + string("/");

	/* your main will always include a similar set up to establish your window
      and GL context, etc. */

	// Set error callback as openGL will report errors but they need a call back
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

	pixW = 640;
	pixH = 480;
	// Create a windowed mode window and its OpenGL context.
	window = glfwCreateWindow(pixW, pixH, "hello triangle", NULL, NULL);
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

	/* This is the code that will likely change program to program as you
		may need to initialize or set up different data and state */
	// Initialize scene.
	init();
	initGeom();

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
