/* Lab 5 base code - transforms using local matrix functions 
   to be written by students - 
	CPE 471 Cal Poly Z. Wood + S. Sueda
*/
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

#include "GLSL.h"
#include "Program.h"
#include "Shape.h"
#include "glm/glm.hpp"

using namespace std;
using namespace glm;

GLFWwindow *window; // Main application window
string RESOURCE_DIR = ""; // Where the resources are loaded from
shared_ptr<Program> prog;
shared_ptr<Shape> shape;

int g_width, g_height;

void printMat(float *A, const char *name = 0)
{
   // OpenGL uses col-major ordering:
   // [ 0  4  8 12]
   // [ 1  5  9 13]
   // [ 2  6 10 14]
   // [ 3  7 11 15]
   // The (i,j)th element is A[i+4*j].
   if(name) {
      printf("%s=[\n", name);
   }
   for(int i = 0; i < 4; ++i) {
      for(int j = 0; j < 4; ++j) {
         printf("%- 5.2f ", A[i+4*j]);
      }
      printf("\n");
   }
   if(name) {
      printf("];");
   }
   printf("\n");
}

void createIdentityMat(float *M)
{
	//set all values to zero
   for(int i = 0; i < 4; ++i) {
      for(int j = 0; j < 4; ++j) {
			M[i*4+j] = 0;
		}
	}
	//overwrite diagonal with 1s
	M[0] = M[5] = M[10] = M[15] = 1;
}

void createTranslateMat(float *T, float x, float y, float z)
{
   //set all values to zero
   for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
         T[i*4+j] = 0;
      }
   }
   //overwrite diagonal values with 1s
   T[0] = T[5] = T[10] = T[15] = 1;

   //set translation values
   T[12] = x;
   T[13] = y;
   T[14] = z;
}


void createScaleMat(float *S, float x, float y, float z)
{
   //set all values to zero
   for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
         S[i*4+j] = 0;
      }
   }
   
   //set scalar values
   S[0] = x;
   S[5] = y;
   S[10] = z;
   S[15] = 1;
}

void createRotateMatX(float *R, float radians)
{ 
   //set all values to zero
   for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
         R[i*4+j] = 0;
      }
   }
   //overwrite diagonal values with 1s
   R[0] = R[5] = R[10] = R[15] = 1;

   R[5] = cos(radians);
   R[6] = sin(radians);
   R[9] = -sin(radians);
   R[10] = cos(radians);
}

void createRotateMatY(float *R, float radians)
{
   //set all values to zero
   for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
         R[i*4+j] = 0;
      }
   }
   //overwrite diagonal values with 1s
   R[0] = R[5] = R[10] = R[15] = 1;

   R[0] = cos(radians);
   R[2] = -sin(radians);
   R[8] = sin(radians);
   R[10] = cos(radians);
}

void createRotateMatZ(float *R, float radians)
{
   //set all values to zero
   for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
         R[i*4+j] = 0;
      }
   }
   //overwrite diagonal values with 1s
   R[0] = R[5] = R[10] = R[15] = 1;

   R[0] = cos(radians);
   R[1] = sin(radians);
   R[4] = -sin(radians);
   R[5] = cos(radians);
}

void multMat(float *C, const float *A, const float *B)
{
   float c = 0;
   for(int k = 0; k < 4; ++k) {
      // Process kth column of C
      for(int i = 0; i < 4; ++i) {
         // Process ith row of C.
         // The (i,k)th element of C is the dot product
         // of the ith row of A and kth col of B.
         c = 0;
         //vector dot
         for(int j = 0; j < 4; ++j) {
            c += A[i+4*j] * B[k*4+j];
         }
         C[i+4*k] = c;
      }
   }
}

void createPerspectiveMat(float *m, float fovy, float aspect, float zNear, float zFar)
{
   // http://www-01.ibm.com/support/knowledgecenter/ssw_aix_61/com.ibm.aix.opengl/doc/openglrf/gluPerspective.htm%23b5c8872587rree
   float f = 1.0f/glm::tan(0.5f*fovy);
   m[ 0] = f/aspect;
   m[ 1] = 0.0f;
   m[ 2] = 0.0f;
   m[ 3] = 0.0f;
   m[ 4] = 0;
   m[ 5] = f;
   m[ 6] = 0.0f;
   m[ 7] = 0.0f;
   m[ 8] = 0.0f;
   m[ 9] = 0.0f;
   m[10] = (zFar + zNear)/(zNear - zFar);
   m[11] = -1.0f;
   m[12] = 0.0f;
   m[13] = 0.0f;
   m[14] = 2.0f*zFar*zNear/(zNear - zFar);
   m[15] = 0.0f;
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
	//local modelview matrix use this for lab 5
   float MV[16] = {0};
	float P[16] = {0};
   float R[16] = {0};
   float S[16] = {0};
   float T[16] = {0};
   float temp[16] = {0};
   float temp2[16] = {0};

	// Get current frame buffer size.
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	// Clear framebuffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Use the local matrices for lab 5
   float aspect = width/(float)height;
   createPerspectiveMat(P, 70.0f, aspect, 0.1, 100.0f);	
	//createIdentityMat(MV);

	//createTranslateMat(MV, 0.0, 0.0, -6.0);
   //createRotateMatY(R, 0.5);
   //multMat(MV, MV, R);
   
   //draw I
   createTranslateMat(T, 0.0, 0.0, -14.0);
   createRotateMatY(R, -0.5);
   multMat(temp, T, R);
   createTranslateMat(T, 4.0, 0.0, 0.0);
   multMat(temp2, temp, T);
   createScaleMat(S, 1.0, 5.0, 1.0);
   multMat(MV, temp2, S);

	// Draw mesh using GLSL.
	prog->bind();
	glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, P);
	glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, MV);
	shape->draw(prog);

   //draw H
   createTranslateMat(T, 0.0, 0.0, -14.0);
   createRotateMatY(R, -0.5);
   multMat(temp, T, R);
   createTranslateMat(T, -4.0, 0.0, 0.0);
   multMat(temp2, temp, T);
   createScaleMat(S, 1.0, 5.0, 1.0);
   multMat(MV, temp2, S);

	glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, P);
	glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, MV);
	shape->draw(prog);

   createTranslateMat(T, 0.0, 0.0, -14.0);
   createRotateMatY(R, -0.5);
   multMat(temp, T, R);
   createScaleMat(S, 1.0, 5.0, 1.0);
   multMat(MV, temp, S);

	glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, P);
	glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, MV);
	shape->draw(prog);

   createTranslateMat(T, 0.0, 0.0, -14.0);
   createRotateMatY(R, -0.5);
   multMat(temp, T, R);
   createTranslateMat(T, -2.0, 0.4, 0.0);
   multMat(temp2, temp, T);
   createRotateMatZ(R, 1.0);
   multMat(temp, temp2, R);
   createScaleMat(S, 0.8, 4.7, 1.0);
   multMat(MV, temp, S);

	glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, P);
	glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, MV);
	shape->draw(prog);

	prog->unbind();
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
