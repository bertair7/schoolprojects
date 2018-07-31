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
shared_ptr<Program> globe;
shared_ptr<Program> mouth;
shared_ptr<Program> note;
shared_ptr<Shape> shape;
shared_ptr<Shape> sphere;

GLuint VertexArrayID;
GLuint vertexbuffer;

int g_width, g_height;
float rotation = 0;

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
   else if (key == GLFW_KEY_A && action == GLFW_PRESS) {
      rotation -= 0.6;
   }
   else if (key == GLFW_KEY_D && action == GLFW_PRESS) {
      rotation += 0.6;
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

static void initGeom() {
   //GLuint normalbuffer;
   GLuint indexbuffer;

   // cylinder vertex data
   GLfloat cyl_vertex_data[240];
   float r = 0.6;
   float z = 0.0;

   for (int i = 0; i < 80; i++) {
      double angle = ((i%20)/20.0)*(2*M_PI);
      if (i != 0 && i%20 == 0) {
         z += 1.0;
      }
      
      float x = r*cos(angle);
      float y = r*sin(angle);

      cyl_vertex_data[i*3] = x;
      cyl_vertex_data[i*3+1] = y;
      cyl_vertex_data[i*3+2] = z;
   }

   glGenVertexArrays(1, &VertexArrayID);
   glBindVertexArray(VertexArrayID);

   glGenBuffers(1, &vertexbuffer);
   glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
   glBufferData(GL_ARRAY_BUFFER, sizeof(cyl_vertex_data), cyl_vertex_data, GL_DYNAMIC_DRAW);

   glEnableVertexAttribArray(0);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

   /* cylinder normal data
   GLint cyl_normal_data[240];
   for (int i = 0; i < 80; i++) {
      vec3 n = vec3(cyl_vertex_data[i*3], 0, cyl_vertex_data[i*3+2]);
      vec3 norm = normalize(n);

      cyl_normal_data[i*3] = norm.x;
      cyl_normal_data[i*3+1] = norm.y;
      cyl_normal_data[i*3+2] = norm.z;
   }

   glGenBuffers(1, &normalbuffer);
   glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
   glBufferData(GL_ARRAY_BUFFER, sizeof(cyl_normal_data), cyl_normal_data, GL_STATIC_DRAW);

   glEnableVertexAttribArray(1);
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
*/
   // cylinder index data
   GLint cyl_index_data[360];
   for (int i = 0; i < 60; i++) {
      cyl_index_data[i*6] = i;
      cyl_index_data[i*6+1] = i+1;
      cyl_index_data[i*6+2] = i+21;

      cyl_index_data[i*6+3] = i;
      cyl_index_data[i*6+4] = i+20;
      cyl_index_data[i*6+5] = i+21;

      if ((i+1)%20 == 0) {
         cyl_index_data[i*6+1] = i-19;
         cyl_index_data[i*6+2] = i+1;
         cyl_index_data[i*6+5] = i+1;
      }
   }

   glGenBuffers(1, &indexbuffer);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cyl_index_data), cyl_index_data, GL_STATIC_DRAW);

   glBindVertexArray(0);
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

   sphere = make_shared<Shape>();
   sphere->loadMesh(RESOURCE_DIR + "sphere.obj");
   sphere->resize();
   sphere->init();

	// Initialize the GLSL program.
	prog = make_shared<Program>();
	prog->setVerbose(true);
	prog->setShaderNames(RESOURCE_DIR + "simple_vert.glsl", RESOURCE_DIR + "simple_frag.glsl");
	prog->init();
	prog->addUniform("P");
	prog->addUniform("MV");
	prog->addAttribute("vertPos");
	prog->addAttribute("vertNor");

   note = make_shared<Program>();
   note->setVerbose(true);
   note->setShaderNames(RESOURCE_DIR + "simple_vert.glsl", RESOURCE_DIR + "notefrag.glsl");
   note->init();
   note->addUniform("center");
   note->addUniform("P");
   note->addUniform("MV");
   note->addAttribute("vertPos");
   note->addAttribute("vertNor");

   mouth = make_shared<Program>();
   mouth->setVerbose(true);
   mouth->setShaderNames(RESOURCE_DIR + "simple_vert.glsl", RESOURCE_DIR + "mouthfrag.glsl");
   mouth->init();
   mouth->addUniform("point");
   mouth->addUniform("P");
   mouth->addUniform("MV");
   mouth->addAttribute("vertPos");
   mouth->addAttribute("vertNor");

   globe = make_shared<Program>();
	globe->setVerbose(true);
   globe->setShaderNames(RESOURCE_DIR + "globe_vert.glsl", RESOURCE_DIR + "globe_frag.glsl");
   globe->init();
	globe->addUniform("P");
	globe->addUniform("MV");
   globe->addUniform("center");
	globe->addAttribute("vertPos");
   globe->addAttribute("vertNor");
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

   float gloRot[16] = {0};
   createRotateMatY(gloRot, rotation);
   float gloTrans[16] = {0};
   createTranslateMat(gloTrans, 0.0, 0.0, -25.0);

	// Get current frame buffer size.
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
  
   float centerX = width/2.0;
   float centerY = height/2.0;

	// Clear framebuffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Use the local matrices for lab 5
   float aspect = width/(float)height;
   createPerspectiveMat(P, 70.0f, aspect, 0.1, 100.0f);	
	prog->bind();
	glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, P);

   //base
   createScaleMat(S, 5.0, 5.0, 5.0);
   multMat(temp, gloRot, S);
   multMat(MV, gloTrans, temp);
	glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, MV);
	sphere->draw(prog);

   //right foot
   createScaleMat(S, 1.0, 0.5, 0.8);
   createTranslateMat(T, 3.0, -8.3, 1.0);
   multMat(temp, S, T);
   multMat(temp2, gloRot, temp);
   multMat(MV, gloTrans, temp2);
	glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, MV);
	sphere->draw(prog);

   //left foot
   createScaleMat(S, 1.0, 0.5, 0.8);
   createTranslateMat(T, -3.0, -8.3, 1.0);
   multMat(temp, S, T);
   multMat(temp2, gloRot, temp);
   multMat(MV, gloTrans, temp2);
	glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, MV);
	sphere->draw(prog);

   //right arm
   createScaleMat(S, 1.2, 0.6, 0.8);
   createRotateMatZ(R, -0.5);
   createTranslateMat(T, 3.6, -2.0, 2.1);
   multMat(temp, R, S);
   multMat(temp2, T, temp);
   multMat(temp, gloRot, temp2);
   multMat(MV, gloTrans, temp);
	glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, MV);
	sphere->draw(prog);

   //left arm
   createScaleMat(S, 1.2, 0.6, 0.8);
   createRotateMatZ(R, 0.5);
   createTranslateMat(T, -3.6, -2.0, 2.1);
   multMat(temp, R, S);
   multMat(temp2, T, temp);
   multMat(temp, gloRot, temp2);
   multMat(MV, gloTrans, temp);
	glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, MV);
	sphere->draw(prog);

   //right ear
   createScaleMat(S, 1.3, 1.9, 0.8);
   createRotateMatZ(R, -0.4);
   createTranslateMat(T, 3.0, 3.0, 0.4);
   multMat(temp, R, S);
   multMat(temp2, T, temp);
   multMat(temp, gloRot, temp2);
   multMat(MV, gloTrans, temp);
	glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, MV);
	sphere->draw(prog);

   //left ear
   createScaleMat(S, 1.3, 1.9, 0.8);
   createRotateMatZ(R, 0.4);
   createTranslateMat(T, -3.0, 3.0, 0.4);
   multMat(temp, R, S);
   multMat(temp2, T, temp);
   multMat(temp, gloRot, temp2);
   multMat(MV, gloTrans, temp);
	glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, MV);
	sphere->draw(prog);

   //left eye
   createScaleMat(S, 1.3, 1.3, 0.7);
   createRotateMatZ(R, 1.5);
   createTranslateMat(T, -1.2, 0.7, 3.7);
   multMat(temp, R, S);
   multMat(temp2, T, temp);
   multMat(temp, gloRot, temp2);
   multMat(MV, gloTrans, temp);
	glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, MV);
	sphere->draw(prog);

   //right eye
   createScaleMat(S, 1.3, 1.3, 0.7);
   createRotateMatZ(R, 1.5);
   createTranslateMat(T, 1.2, 0.7, 3.7);
   multMat(temp, R, S);
   multMat(temp2, T, temp);
   multMat(temp, gloRot, temp2);
   multMat(MV, gloTrans, temp);
	glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, MV);
	sphere->draw(prog);

	prog->unbind();

   //music note
   note->bind();

   //music note stem
   createScaleMat(S, 0.8, 1.5, 0.7);
   createRotateMatX(R, 1.5);
   createTranslateMat(T, 5.0, 2.0, 4.0);
   multMat(temp, S, R);
   createRotateMatY(R, glfwGetTime());
   multMat(temp2, R, temp);
   multMat(temp, T, temp2);
   multMat(temp2, gloRot, temp);
   multMat(MV, gloTrans, temp2);
   glUniform2f(globe->getUniform("center"), centerX, centerY);
	glUniformMatrix4fv(mouth->getUniform("P"), 1, GL_FALSE, P);
	glUniformMatrix4fv(note->getUniform("MV"), 1, GL_FALSE, MV);
   glBindVertexArray(VertexArrayID);
   glDrawElements(GL_TRIANGLES, 360, GL_UNSIGNED_INT, 0);
   
   //music note hat
   createScaleMat(S, 0.8, 0.5, 0.7);
   createRotateMatX(R, 0.7);
   createTranslateMat(T, 5.0, 1.85, 4.0);
   multMat(temp, S, R);
   createRotateMatY(R, 1.4);
   multMat(temp2, R, temp);
   createRotateMatY(R, glfwGetTime());
   multMat(temp, R, temp2);
   multMat(temp2, T, temp);
   multMat(temp, gloRot, temp2);
   multMat(MV, gloTrans, temp);
	glUniformMatrix4fv(note->getUniform("MV"), 1, GL_FALSE, MV);
   glBindVertexArray(VertexArrayID);
   glDrawElements(GL_TRIANGLES, 360, GL_UNSIGNED_INT, 0);

   //music note bulb
   createScaleMat(S, 1.2, 0.5, 0.7);
   createRotateMatY(R, glfwGetTime());
   createTranslateMat(T, -0.6, -0.5, 0.0);
   multMat(temp, S, T);
   multMat(temp2, R, temp);
   createTranslateMat(T, 5.0, -2.0, 4.0);
   multMat(temp, T, temp2);
   multMat(temp2, gloRot, temp);
   multMat(MV, gloTrans, temp2);
	glUniformMatrix4fv(note->getUniform("MV"), 1, GL_FALSE, MV);
   sphere->draw(note);

   note->unbind();

   //mouth
   mouth->bind();
   createScaleMat(S, 0.9, 0.7, 0.8);
   createTranslateMat(T, 0.0, -2.0, 4.7);
   multMat(temp, S, T);
   multMat(temp2, gloRot, temp);
   multMat(MV, gloTrans, temp2);
  
   glUniform2f(mouth->getUniform("point"), centerX, (centerY-50.0));
	glUniformMatrix4fv(mouth->getUniform("P"), 1, GL_FALSE, P);
	glUniformMatrix4fv(mouth->getUniform("MV"), 1, GL_FALSE, MV);
	sphere->draw(mouth);
   
   mouth->unbind();

   //globe
   globe->bind();

   createScaleMat(S, 11.0, 11.0, 11.0);
   multMat(temp, gloRot, S);
   multMat(MV, gloTrans, temp);
   glUniform2f(globe->getUniform("center"), centerX, centerY);
	glUniformMatrix4fv(globe->getUniform("P"), 1, GL_FALSE, P);
	glUniformMatrix4fv(globe->getUniform("MV"), 1, GL_FALSE, MV);
   sphere->draw(globe);

   globe->unbind();
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
