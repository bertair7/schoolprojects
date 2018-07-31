/* 
	2017 Program 3 revise - set up to handle multiple shapes - students
	must complete code
*/
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GLSL.h"
#include "Program.h"
#include "MatrixStack.h"
#include "Shape.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

// value_ptr for glm
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;

/* to use glee */
#define GLEE_OVERWRITE_GL_FUNCTIONS
#include "glee.hpp"

#define M_PI 3.1415926535897932384626433832795

GLFWwindow *window; // Main application window
string RESOURCE_DIR = ""; // Where the resources are loaded from
shared_ptr<Program> prog;

//a vector of smart pointers for all the shapes in one .obj file
std::vector<shared_ptr<Shape>> AllShapes;

int g_width, g_height;
float g_rotate = 0;
vec3 g_trans;
float g_scale = 1;
float light_trans = 0;
int material = 0;

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
		g_rotate += 0.1;
	}
   else if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		g_rotate -= 0.1;
	}
   else if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
		light_trans -= 1;
	}
   else if (key == GLFW_KEY_E && action == GLFW_PRESS) {
		light_trans += 1;
	}
   else if (key == GLFW_KEY_M && action == GLFW_PRESS) {
		material += 1;
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

	// Load geometry
 	// Some obj files contain material information.
 	// We'll ignore them for this assignment.
	//this is the tiny obj shapes - not to be confused with our shapes
 	vector<tinyobj::shape_t> TOshapes;
 	vector<tinyobj::material_t> objMaterials;
 	string errStr;
	//load in the mesh and make the shapes
 	bool rc = tinyobj::LoadObj(TOshapes, objMaterials, errStr, (RESOURCE_DIR + "dummy.obj").c_str());
	 if(!rc) {
 		cerr << errStr << endl;
 	  } else {
		//some data to keep track of where our mesh is in space
		vec3 Gmin, Gmax, avg;
      float longest;

		Gmin = vec3(1.1754E+38F);
		Gmax = vec3(-1.1754E+38F);
      avg = vec3(0);

		for (int i=0; i < TOshapes.size(); i++) {
			// TODO -- Initialize each mesh
 			//1. make a shared pointer
			shared_ptr<Shape> s = make_shared<Shape>();
			// 2. createShape for each tiny obj shape
			s->createShape(TOshapes[i]);
			// 3. measure each shape to find out its AABB
			s->measure();
			// 4. call init on each shape to create the GPU data
			s->init();
			//perform some record keeping to keep track of global min and max
			if (Gmin.x > s->min.x)
            Gmin.x = s->min.x;
			if (Gmin.y > s->min.y)
            Gmin.y = s->min.y;
			if (Gmin.z > s->min.z)
            Gmin.z = s->min.z;

			if (Gmax.x < s->max.x)
            Gmax.x = s->max.x;
			if (Gmax.y < s->max.y)
            Gmax.y = s->max.y;
			if (Gmax.z < s->max.z)
            Gmax.z = s->max.z;
			//Add the shape to AllShapes
         AllShapes.push_back(s); 
		}

		//fix these based on the results of calling measure on each piece	
	   avg.x = (Gmin.x + Gmax.x)/2.0;
      avg.y = (Gmin.y + Gmax.y)/2.0;
      avg.z = (Gmin.z + Gmax.z)/2.0;
      g_trans = -avg;

      if (avg.x > avg.y) {
         if (avg.x > avg.z)
            longest = avg.x;
         else
            longest = avg.z;
      }
      else {
         if (avg.y > avg.z)
            longest = avg.y;
         else
            longest = avg.z;
      }
		g_scale = 1/longest;

		cout << "global scale " << g_scale << endl;
		cout << "global trans " << g_trans.x << " " << g_trans.y << " " << g_trans.z << endl;
	  }

}


static void init()
{
	GLSL::checkVersion();

	// Set background color.
	glClearColor(.12f, .34f, .56f, 1.0f);
	// Enable z-buffer test.
	glEnable(GL_DEPTH_TEST);

	// Initialize the GLSL program.
	prog = make_shared<Program>();
	prog->setVerbose(true);
	prog->setShaderNames(RESOURCE_DIR + "simple_vert.glsl", RESOURCE_DIR + "simple_frag.glsl");
	prog->init();
	prog->addUniform("kd");
	prog->addUniform("ks");
	prog->addUniform("ka");
	prog->addUniform("IL");
	prog->addUniform("light");
   prog->addUniform("shine");
	prog->addUniform("P");
	prog->addUniform("MV");
	prog->addAttribute("vertPos");
	prog->addAttribute("vertNor");
	prog->addAttribute("vertTex");
}

static void setMaterial(int i) {
   int m = i % 4;
   switch(m) {
      case 0: //shiny blue plastic
         glUniform3f(prog->getUniform("ka"), 0.02, 0.04, 0.2);
         glUniform3f(prog->getUniform("kd"), 0.0, 0.16, 0.9);
         glUniform3f(prog->getUniform("ks"), 0.14, 0.2, 0.8);
         glUniform1f(prog->getUniform("shine"), 120.0);
         break;
      case 1: //flat gray
         glUniform3f(prog->getUniform("ka"), 0.13, 0.13, 0.14);
         glUniform3f(prog->getUniform("kd"), 0.3, 0.3, 0.4);
         glUniform3f(prog->getUniform("ks"), 0.3, 0.3, 0.4);
         glUniform1f(prog->getUniform("shine"), 4.0);
         break;
      case 2: //brass
         glUniform3f(prog->getUniform("ka"), 0.3294, 0.2235, 0.02745);
         glUniform3f(prog->getUniform("kd"), 0.7804, 0.5686, 0.11373);
         glUniform3f(prog->getUniform("ks"), 0.9922, 0.941176, 0.80784);
         glUniform1f(prog->getUniform("shine"), 27.9);      
         break;
      case 3: //ruby - see README
         glUniform3f(prog->getUniform("ka"), 0.1745, 0.01175, 0.01175);
         glUniform3f(prog->getUniform("kd"), 0.61424, 0.04136, 0.04136);
         glUniform3f(prog->getUniform("ks"), 0.727811, 0.626959, 0.626959);
         glUniform1f(prog->getUniform("shine"), 76.8);      
         break;
   }
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

	prog->bind();
	glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, value_ptr(P->topMatrix()));
   glUniform3f(prog->getUniform("IL"), 1.0, 1.0, 1.0);
   glUniform3f(prog->getUniform("light"), -2.0+light_trans, 2.0, 2.0);
   setMaterial(material);
   
	/* draw right mesh */	
   MV->pushMatrix();
      MV->loadIdentity();
	  	MV->translate(vec3(0, 0, -4));
      MV->translate(vec3(1.3, 0, 0));
      MV->rotate(M_PI/2.0, vec3(0, 1, 0));
	  	MV->rotate(-1.5, vec3(1, 0, 0));
	  	MV->scale(g_scale);
	  	MV->translate(g_trans);
	  	glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, value_ptr(MV->topMatrix()));

		//iterate through all the shapes and draw them
		for (int i=0; i < AllShapes.size(); i++) {		
	  		AllShapes[i]->draw(prog);
		}
		
   MV->popMatrix();

   setMaterial(material+1);
	/* draw left mesh */	
   MV->pushMatrix();
      MV->loadIdentity();
	  	MV->translate(vec3(0, 0, -4));
      MV->translate(vec3(-1.3, 0, 0));
      MV->rotate(M_PI/2.0+g_rotate, vec3(0, 1, 0));
	  	MV->rotate(-1.65, vec3(1, 0, 0));
	  	MV->scale(g_scale);
	  	MV->translate(g_trans);
	  	glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, value_ptr(MV->topMatrix()));

		//iterate through all the shapes and draw them
		for (int i=0; i < AllShapes.size(); i++) {		
	  		AllShapes[i]->draw(prog);
		}
		
   MV->popMatrix();

	prog->unbind();

   // Pop matrix stacks.
   P->popMatrix();

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
	window = glfwCreateWindow(640, 480, "Ryan Blair", NULL, NULL);
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
