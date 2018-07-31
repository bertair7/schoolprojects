/* Base code for texture mapping lab */
/* includes three images and three meshes - Z. Wood 2016 */
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

#include "GLSL.h"
#include "Program.h"
#include "MatrixStack.h"
#include "Shape.h"
#include "Texture.h"

// value_ptr for glm
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

/* to use glee */
#define GLEE_OVERWRITE_GL_FUNCTIONS
#include "glee.hpp"

using namespace std;
using namespace glm;

GLFWwindow *window; // Main application window
string RESOURCE_DIR = ""; // Where the resources are loaded from
shared_ptr<Program> prog0, prog1, prog2, prog3;
shared_ptr<Shape> world, shape, cactus;
shared_ptr<Texture> texture0, texture1, texture2, texture3, texture4;

std::vector<shared_ptr<Shape>> AllShapes;

int g_GiboLen, g_width, g_height;
vec3 g_trans, eye, LookAt, upV, view, u, v, w;
GLfloat positions[30][3];

float g_scale = 1.0;
float g_rotate = 0.0;
float cTheta = 0.0;
float cHeight = 0.0;
float t = 0.0;
float lWidth = 0.0;
float lHeight = 64.0;
float alpha = 0.0;
float beta = 90.0;
bool day = true;

//global data for ground plane
GLuint GrndBuffObj, GrndNorBuffObj, GrndTexBuffObj, GIndxBuffObj;

static void error_callback(int error, const char *description)
{
	cerr << description << endl;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
   } else if (key == GLFW_KEY_W && action == GLFW_PRESS) {
      eye -= 0.5f * w;
      LookAt -= 0.5f * w;
   } else if (key == GLFW_KEY_A && action == GLFW_PRESS) {
      eye -= 0.5f * u;
      LookAt -= 0.5f * u;
   } else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
      eye += 0.5f * w;
      LookAt += 0.5f * w;
   } else if (key == GLFW_KEY_D && action == GLFW_PRESS) {
      eye += 0.5f * u;
      LookAt += 0.5f * u;
   } else if (key == GLFW_KEY_T && action == GLFW_PRESS) {
      if (day) {
         day = false;
         t += 2*M_PI;
         lHeight = (float)(64.0 * cos(t));
         lWidth = (float)(64.0 * sin(t));
      } else {
         day = true;
         t -= 2*M_PI;
         lHeight = (float)(64.0 * cos(t));
         lWidth = (float)(64.0 * sin(t));
      }
   } else if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
      t += 0.05;
      lHeight = (float)(64.0 * cos(t));
      lWidth = (float)(64.0 * sin(t));
   } else if (key == GLFW_KEY_E && action == GLFW_PRESS) {
      t -= 0.05;
      lHeight = (float)(64.0 * cos(t));
      lWidth = (float)(64.0 * sin(t));
   }
}

static void resize_callback(GLFWwindow *window, int width, int height) {
	g_width = width;
	g_height = height;
	glViewport(0, 0, width, height);
}

static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
   int width, height;
   glfwGetFramebufferSize(window, &width, &height);
   
   beta = (float)(M_PI*3.0 * (xpos/(float)width));
   alpha = (float)(M_PI * (ypos/(float)height) - radians(80.0f));
}

float p2wx(double in_x, float left) {
	float c = (-2*left)/(g_width-1.0);
	float d = left;
   return c*in_x+d;
}

float p2wy(double in_y, float bot) {
	//flip y
  	in_y = g_height -in_y;
	float e = (-2*bot)/(g_height-1.0);
	float f = bot;
   return e*in_y + f;
}

/* code to define the ground plane */
static void initGeom() {   
   float g_groundSize = 6000;
   float g_groundY = -1.5;

  // A x-z plane at y = g_groundY of dimension [-g_groundSize, g_groundSize]^2
    float GrndPos[] = {
    -g_groundSize, g_groundY, -g_groundSize,
    -g_groundSize, g_groundY,  g_groundSize,
     g_groundSize, g_groundY,  g_groundSize,
     g_groundSize, g_groundY, -g_groundSize
    };

    float GrndNorm[] = {
     0, 1, 0,
     0, 1, 0,
     0, 1, 0,
     0, 1, 0,
     0, 1, 0,
     0, 1, 0
    };

  static GLfloat GrndTex[] = {
      0, 0, // back
      0, 5,
      5, 5,
      5, 0 };

   unsigned short idx[] = {0, 1, 2, 0, 2, 3};

   GLuint VertexArrayID;
	//generate the VAO
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

   g_GiboLen = 6;
   glGenBuffers(1, &GrndBuffObj);
   glBindBuffer(GL_ARRAY_BUFFER, GrndBuffObj);
   glBufferData(GL_ARRAY_BUFFER, sizeof(GrndPos), GrndPos, GL_STATIC_DRAW);

   glGenBuffers(1, &GrndNorBuffObj);
   glBindBuffer(GL_ARRAY_BUFFER, GrndNorBuffObj);
   glBufferData(GL_ARRAY_BUFFER, sizeof(GrndNorm), GrndNorm, GL_STATIC_DRAW);
    
	glGenBuffers(1, &GrndTexBuffObj);
   glBindBuffer(GL_ARRAY_BUFFER, GrndTexBuffObj);
   glBufferData(GL_ARRAY_BUFFER, sizeof(GrndTex), GrndTex, GL_STATIC_DRAW);

   glGenBuffers(1, &GIndxBuffObj);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GIndxBuffObj);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);

   // Set random points for cacti models
   for (int i = 0; i < 30; i++) {
      float x = -60.0 + (rand() % 120);
      float z = -60.0 + (rand() % 120);
      positions[i][0] = x;
      positions[i][1] = 0.0;
      positions[i][2] = z;
   }

}

static void init()
{
	GLSL::checkVersion();

   eye = vec3(0.0, 3.0, 0.0);
   LookAt = vec3(0.0, 3.0, -1.0);
   upV = vec3(0.0, 1.0, 0.0);
   
   view = LookAt - eye;
   w = -1.0f * (view/length(view));
   u = normalize(cross(upV, w));
   v = normalize(cross(w, u));

	// Set background color.
	glClearColor(0.1f+0.4*sin(t), 0.1f+0.5*cos(t), 0.3f+0.5*cos(t), 1.0f);
	// Enable z-buffer test.
	glEnable(GL_DEPTH_TEST);

  // Initialize mesh.
   shape = make_shared<Shape>();
   shape->loadMesh(RESOURCE_DIR + "dog.obj");
   shape->resize();
   shape->init();
   
	world = make_shared<Shape>();
   world->loadMesh(RESOURCE_DIR + "sphere.obj");
   world->resize();
   world->init();

   cactus = make_shared<Shape>();
   cactus->loadMesh(RESOURCE_DIR + "cactus_obj.obj");
   cactus->resize();
   cactus->init();

	// Initialize the GLSL programs
	prog0 = make_shared<Program>();
	prog0->setVerbose(true);
	prog0->setShaderNames(RESOURCE_DIR + "tex_vert.glsl", RESOURCE_DIR + "tex_frag0.glsl");
	prog0->init();
	
	prog1 = make_shared<Program>();
	prog1->setVerbose(true);
	prog1->setShaderNames(RESOURCE_DIR + "tex_vert.glsl", RESOURCE_DIR + "tex_frag1.glsl");
	prog1->init();
  
	prog2 = make_shared<Program>();
	prog2->setVerbose(true);
	prog2->setShaderNames(RESOURCE_DIR + "tex_vert.glsl", RESOURCE_DIR + "tex_frag2.glsl");
	prog2->init();
	
	prog3 = make_shared<Program>();
	prog3->setVerbose(true);
	prog3->setShaderNames(RESOURCE_DIR + "tex_vert.glsl", RESOURCE_DIR + "tex_frag3.glsl");
	prog3->init();
	
	//////////////////////////////////////////////////////
   // Intialize textures
   //////////////////////////////////////////////////////
	texture0 = make_shared<Texture>();
   texture0->setFilename(RESOURCE_DIR + "fur.jpg");
   texture0->init();
   texture0->setUnit(0);
   texture0->setWrapModes(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

   texture1 = make_shared<Texture>();
   texture1->setFilename(RESOURCE_DIR + "sun.jpg");
   texture1->init();
   texture1->setUnit(1);
   texture1->setWrapModes(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
   
	texture2 = make_shared<Texture>();
   texture2->setFilename(RESOURCE_DIR + "sand_texture.jpg");
   texture2->init();
   texture2->setUnit(2);
   texture2->setWrapModes(GL_REPEAT, GL_REPEAT);

   texture3 = make_shared<Texture>();
   texture3->setFilename(RESOURCE_DIR + "moon.jpg");
   texture3->init();
   texture3->setUnit(3);
   texture3->setWrapModes(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
   
   texture4 = make_shared<Texture>();
   texture4->setFilename(RESOURCE_DIR + "cactus1.png");
   texture4->init();
   texture4->setUnit(4);
   texture4->setWrapModes(GL_REPEAT, GL_REPEAT);
   
	/// Add uniform and attributes to each of the programs
	prog0->addUniform("P");
	prog0->addUniform("M");
	prog0->addUniform("V");
	prog0->addAttribute("vertPos");
   prog0->addAttribute("vertNor");
	prog0->addAttribute("vertTex");
   prog0->addUniform("light");
   prog0->addUniform("IL");
   prog0->addUniform("Texture0");
	
	prog1->addUniform("P");
	prog1->addUniform("M");
	prog1->addUniform("V");
	prog1->addAttribute("vertPos");
   prog1->addAttribute("vertNor");
	prog1->addAttribute("vertTex");
   prog1->addUniform("light");
   prog1->addUniform("IL");
   prog1->addUniform("Texture1");
	
	prog2->addUniform("P");
	prog2->addUniform("M");
	prog2->addUniform("V");
	prog2->addAttribute("vertPos");
   prog2->addAttribute("vertNor");
	prog2->addAttribute("vertTex");
   prog2->addUniform("light");
   prog2->addUniform("IL");
   prog2->addUniform("Texture2");

	prog3->addUniform("P");
	prog3->addUniform("M");
	prog3->addUniform("V");
	prog3->addAttribute("vertPos");
   prog3->addAttribute("vertNor");
	prog3->addAttribute("vertTex");
   prog3->addUniform("light");
   prog3->addUniform("IL");
   prog3->addUniform("Texture3");

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

	// Set background color.
	glClearColor(0.1f+0.4*sin(t), 0.1f+0.5*cos(t), 0.3f+0.5*cos(t), 1.0f);
	// Clear framebuffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // redefine LookAt angle
   LookAt.x = eye.x + (1.0 * cos(alpha) * cos(beta));
   LookAt.y = eye.y + (1.0 * sin(alpha));
   LookAt.z = eye.z + (1.0 * cos(alpha) * sin(beta));

   // update view vectors
   view = LookAt - eye;
   w = -1.0f * (view/length(view));
   u = normalize(cross(upV, w));
   v = normalize(cross(w, u));

	// Create the matrix stacks 
	auto P = make_shared<MatrixStack>();
	auto V = make_shared<MatrixStack>();
	auto M = make_shared<MatrixStack>();
	P->pushMatrix();
   P->perspective(45.0f, aspect, 0.01f, 100.0f);

   V->pushMatrix();
   V->lookAt(eye, LookAt, upV);

   //draw cacti
	prog0->bind();
	glUniformMatrix4fv(prog0->getUniform("P"), 1, GL_FALSE, value_ptr(P->topMatrix()));
	glUniformMatrix4fv(prog0->getUniform("V"), 1, GL_FALSE, value_ptr(V->topMatrix()));

   if (lHeight > 31) {
      glUniform3f(prog0->getUniform("light"), lWidth, lHeight+1, 0.0);
      glUniform1f(prog0->getUniform("IL"), 1.0);
   }
   else if (lHeight > 0) {
      glUniform3f(prog0->getUniform("light"), lWidth, lHeight+1, 0.0);
      glUniform1f(prog0->getUniform("IL"), 0.5);
   }
   else {
      glUniform3f(prog0->getUniform("light"), -lWidth/2.0, (-lHeight-1)/2.0, 0.0);
      glUniform1f(prog0->getUniform("IL"), 0.2);
   }

   texture4->bind(prog0->getUniform("Texture0"));
   for (int i = 0; i < 30; i++) {
      M->pushMatrix();
      M->loadIdentity();
      M->translate(vec3(positions[i][0], positions[i][1], positions[i][2]));
      M->scale(7);
      M->translate(vec3(0, 1, 0));
	   glUniformMatrix4fv(prog0->getUniform("M"), 1, GL_FALSE, value_ptr(M->topMatrix()));
      cactus->draw(prog0);      

      M->popMatrix();
   }
	prog0->unbind();

	//draw the dog mesh 	
   prog3->bind();
   texture0->bind(prog3->getUniform("Texture3"));
	glUniformMatrix4fv(prog3->getUniform("P"), 1, GL_FALSE, value_ptr(P->topMatrix()));
	glUniformMatrix4fv(prog3->getUniform("V"), 1, GL_FALSE, value_ptr(V->topMatrix()));
   glUniform3f(prog3->getUniform("light"), lWidth, lHeight+1, 0.0);
   glUniform1f(prog3->getUniform("IL"), 2.0);
	
   if (lHeight > 31) {
      glUniform3f(prog3->getUniform("light"), lWidth, lHeight+1, 0.0);
      glUniform1f(prog3->getUniform("IL"), 1.0);
   }
   else if (lHeight > 0) {
      glUniform3f(prog3->getUniform("light"), lWidth, lHeight+1, 0.0);
      glUniform1f(prog3->getUniform("IL"), 0.5);
   }
   else {
      glUniform3f(prog3->getUniform("light"), -lWidth/2.0, (-lHeight-1)/2.0, 0.0);
      glUniform1f(prog3->getUniform("IL"), 0.2);
   }

	M->pushMatrix();
   M->translate(vec3(-1, 0, 5));
   M->rotate(cTheta, vec3(0, 1, 0));
	glUniformMatrix4fv(prog3->getUniform("M"), 1, GL_FALSE, value_ptr(M->topMatrix()));

   shape->draw(prog3);
	M->popMatrix();

   prog3->unbind();

	//draw the sun
	prog1->bind(); 
	glUniformMatrix4fv(prog1->getUniform("P"), 1, GL_FALSE, value_ptr(P->topMatrix()));
	glUniformMatrix4fv(prog1->getUniform("V"), 1, GL_FALSE, value_ptr(V->topMatrix()));
	
   if (lHeight > 0) {
      glUniform3f(prog1->getUniform("light"), lWidth, lHeight+1, 0.0);
      glUniform1f(prog1->getUniform("IL"), 0.1);
   }
   else {
      glUniform3f(prog1->getUniform("light"), -lWidth/2.0, (-lHeight-1)/2.0, 0.0);
      glUniform1f(prog1->getUniform("IL"), 0.1);
   }

   /*if (day) {
      texture1->bind(prog1->getUniform("Texture1"));
   }
   else {
      texture3->bind(prog1->getUniform("Texture1"));
   }
	M->pushMatrix();
	M->translate(vec3(lWidth, lHeight, 0));
   M->rotate(cTheta, vec3(0, 1, 0));
	glUniformMatrix4fv(prog1->getUniform("M"), 1, GL_FALSE, value_ptr(M->topMatrix()));
    
	world->draw(prog1);
   M->popMatrix();*/

   //draw the moon
   if (!day) {
      texture1->bind(prog1->getUniform("Texture1"));
   }
   else {
      texture3->bind(prog1->getUniform("Texture1"));
   }
      
	M->pushMatrix();
	M->translate(vec3(-lWidth/2.0, -lHeight/2.0, 0));
   M->rotate(0.6, vec3(1, 0, 1));
	glUniformMatrix4fv(prog1->getUniform("M"), 1, GL_FALSE, value_ptr(M->topMatrix()));
    
	world->draw(prog1);
   
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	M->popMatrix();
	prog1->unbind();

	//draw the ground plane	
	prog2->bind();
	M->pushMatrix();
   texture2->bind(prog2->getUniform("Texture2"));
	glUniformMatrix4fv(prog2->getUniform("P"), 1, GL_FALSE, value_ptr(P->topMatrix()));
	glUniformMatrix4fv(prog2->getUniform("V"), 1, GL_FALSE, value_ptr(V->topMatrix()));
	glUniformMatrix4fv(prog2->getUniform("M"), 1, GL_FALSE, value_ptr(M->topMatrix()));

   if (lHeight > 31) {
      glUniform3f(prog2->getUniform("light"), lWidth, lHeight+1, 0.0);
      glUniform1f(prog2->getUniform("IL"), 1.0);
   }
   else if (lHeight > 0) {
      glUniform3f(prog2->getUniform("light"), lWidth, lHeight+1, 0.0);
      glUniform1f(prog2->getUniform("IL"), 0.6);
   }
   else {
      glUniform3f(prog2->getUniform("light"), -lWidth/2.0, (-lHeight-1)/2.0, 0.0);
      glUniform1f(prog2->getUniform("IL"), 0.3);
   }

	glEnableVertexAttribArray(0);
   glBindBuffer(GL_ARRAY_BUFFER, GrndBuffObj);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);
   glBindBuffer(GL_ARRAY_BUFFER, GrndNorBuffObj);
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	 
	glEnableVertexAttribArray(2);
   glBindBuffer(GL_ARRAY_BUFFER, GrndTexBuffObj);
   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

   // draw!
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GIndxBuffObj);
   glDrawElements(GL_TRIANGLES, g_GiboLen, GL_UNSIGNED_SHORT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	
	M->popMatrix();
	prog2->unbind();

	P->popMatrix();
	V->popMatrix();
}

int main(int argc, char **argv)
{

	g_width = 1000;
	g_height = 1000;
	/* we will always need to load external shaders to set up where */
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

	// Create a windowed mode window and its OpenGL context.
	window = glfwCreateWindow(g_width, g_height, "Ryan Blair", NULL, NULL);
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
	//set the window resize call back
	glfwSetFramebufferSizeCallback(window, resize_callback);
	//set the mouse position call back
	glfwSetCursorPosCallback(window, cursor_position_callback);

	/* This is the code that will likely change program to program as you
		may need to initialize or set up different data and state */
	// Initialize scene.
	initGeom();
	cout << "done initializing geometry" << endl;
	init();
	cout << "done initializing shaders" << endl;

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
