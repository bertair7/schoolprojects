/* 
	2017 Program 3 revise - set up to handle multiple shapes - students
	must complete code
*/
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

#include "GLSL.h"
#include "Program.h"
#include "MatrixStack.h"
#include "Shape.h"
#include "GLTextureWriter.h"

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

GLFWwindow *window; // Main application window
string RESOURCE_DIR = ""; // Where the resources are loaded from
shared_ptr<Program> prog, tex_prog;
shared_ptr<Shape> cube, shape;

//a vector of smart pointers for all the shapes in one .obj file
std::vector<shared_ptr<Shape>> AllShapes;

//global reference to texture FBO
GLuint frameBuf;
GLuint texBuf;
GLuint depthBuf;

//gerometry for texture render
GLuint quad_VertexArrayID;
GLuint quad_vertexbuffer;
GLuint quad_texturebuffer;

int g_width, g_height;
vec3 g_trans, eye, LookAt, upV, view, u, v, w, portalEye, portalLookAt;
GLfloat positions[25][3], positions2[25][3];

float g_rotate = 0.0;
float g_scale = 1.0;
float light_trans = 0.0;
float alpha = 0.0;
float beta = 90.0;
int material = 0;
int FirstTime = 1;

static void error_callback(int error, const char *description)
{
	cerr << description << endl;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	} 
   else if (key == GLFW_KEY_W && action == GLFW_PRESS) { //forward
	   eye -= 0.5f * w;
	   LookAt -= 0.5f * w;
	}
   else if (key == GLFW_KEY_A && action == GLFW_PRESS) { //left
	   eye -= 0.5f * u;
	   LookAt -= 0.5f * u;
	}
   else if (key == GLFW_KEY_S && action == GLFW_PRESS) { //backward
	   eye += 0.5f * w;
	   LookAt += 0.5f * w;
	}
   else if (key == GLFW_KEY_D && action == GLFW_PRESS) { //right
	   eye += 0.5f * u;
	   LookAt += 0.5f * u;
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

static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
   int width, height;
   glfwGetFramebufferSize(window, &width, &height);

   beta = (float)(M_PI*3.0 * (xpos/(float)width));
   alpha = (float)(M_PI * (ypos/(float)height) - radians(80.0f));
}

static void resize_callback(GLFWwindow *window, int width, int height) {
   g_width = width;
   g_height = height;
   glViewport(0, 0, width, height);
}

static void createFBO(GLuint& fb, GLuint& tex) {
   //initialize FBO (global memory)
   int width, height;
   glfwGetFramebufferSize(window, &width, &height);
   
   //set up framebuffer
   glBindFramebuffer(GL_FRAMEBUFFER, fb);
   //set up texture
   glBindTexture(GL_TEXTURE_2D, tex);

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

   glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);

   if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) { 
      cout << "Error setting up frame buffer - exiting" << endl;
      exit(0);
   }
}

static void initQuad() {
   // set up simple quad for rendering FBO
   glGenVertexArrays(1, &quad_VertexArrayID);
   glBindVertexArray(quad_VertexArrayID);

   static const GLfloat g_quad_vertex_buffer_data[] = {
      -1.0f, -1.0f, 0.0f,
      1.0f, -1.0f, 0.0f,
      -1.0f, 1.0f, 0.0f, 
      -1.0f, 1.0f, 0.0f,
      1.0f, -1.0f, 0.0f,
      1.0f, 1.0f, 0.0f
   };

   glGenBuffers(1, &quad_vertexbuffer);
   glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
   glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);
   /*
   static const GLfloat g_quad_texture_buffer_data[] = {
      0, 0,      
      0, 1,
      1, 1,
      1, 0
   };

   glGenBuffers(1, &quad_texturebuffer);
   glBindBuffer(GL_ARRAY_BUFFER, quad_texturebuffer);
   glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_texture_buffer_data), g_quad_texture_buffer_data, GL_STATIC_DRAW);
*/
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
 			// make a shared pointer
			shared_ptr<Shape> s = make_shared<Shape>();
			// createShape for each tiny obj shape
			s->createShape(TOshapes[i]);
			// measure each shape to find out its AABB
			s->measure();
			// call init on each shape to create the GPU data
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
   int width, height;
   glfwGetFramebufferSize(window, &width, &height);

   eye = vec3(0.0, 3.0, 0.0);
   LookAt = vec3(0.0, 3.0, -1.0);
   upV = vec3(0.0, 1.0, 0.0);
   portalEye = vec3(0.0, 0.0, 4.0);
   portalLookAt = vec3(0.0, 0.0, 3.0);

   view = LookAt - eye;
   w = -1.0f * (view/length(view));
   u = normalize(cross(upV, w));
   v = normalize(cross(w, u));

   // Set random points for models
   for (int i = 0; i < 25; i++) {
      float x = -15.0 + (rand() % 30);
      float z = -15.0 + (rand() % 30);
      positions[i][0] = x;
      positions[i][1] = 0.0;
      positions[i][2] = z;
   }

   for (int i = 0; i < 25; i++) {
      float x = -15.0 + (rand() % 30);
      float z = -15.0 + (rand() % 30);
      positions2[i][0] = x;
      positions2[i][1] = 0.0;
      positions2[i][2] = z;
   }

	// Set background color.
	glClearColor(.12f, .34f, .56f, 1.0f);
	// Enable z-buffer test.
	glEnable(GL_DEPTH_TEST);

   // Initialize the geometry to render a quad to the screen
   initQuad();

   // Initialize meshes
   cube = make_shared<Shape>();
   cube->loadMesh(RESOURCE_DIR + "cube.obj");
   cube->resize();
   cube->init();

   shape = make_shared<Shape>();
   shape->loadMesh(RESOURCE_DIR + "Nefertiti-100K.obj");
   shape->resize();
   shape->init();

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
	prog->addUniform("M");
   prog->addUniform("V");
	prog->addAttribute("vertPos");
	prog->addAttribute("vertNor");
	prog->addAttribute("vertTex");

   // set up shaders to hold fbo of scene
   tex_prog = make_shared<Program>();
   tex_prog->setVerbose(true);
   tex_prog->setShaderNames(RESOURCE_DIR + "texvert.glsl", RESOURCE_DIR + "texfrag.glsl");
   tex_prog->init();
   tex_prog->addUniform("P");
   tex_prog->addUniform("M");
   tex_prog->addUniform("V");
   tex_prog->addUniform("texBuf");
   tex_prog->addAttribute("vertPos");
   //tex_prog->addAttribute("inCoords");

   // create fbo for portal
   glGenFramebuffers(1, &frameBuf);
   glGenTextures(1, &texBuf);
   glGenRenderbuffers(1, &depthBuf);
   createFBO(frameBuf, texBuf);

   // set up depth
   glBindRenderbuffer(GL_RENDERBUFFER, depthBuf);
   glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
   glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuf);

   GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
   glDrawBuffers(1, DrawBuffers);
   
}

static void ProcessImage(GLuint inTex, float aspect) {
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, inTex);

   tex_prog->bind();

   auto P = make_shared<MatrixStack>();
   auto V = make_shared<MatrixStack>();
   auto M = make_shared<MatrixStack>();

   P->pushMatrix();
   P->perspective(45.0f, aspect, 0.01f, 100.0f);
   V->pushMatrix();
   V->lookAt(eye, LookAt, upV);

	glUniformMatrix4fv(tex_prog->getUniform("P"), 1, GL_FALSE, value_ptr(P->topMatrix()));
	glUniformMatrix4fv(tex_prog->getUniform("V"), 1, GL_FALSE, value_ptr(V->topMatrix()));

   M->pushMatrix();
      M->loadIdentity();
      M->translate(vec3(0, 0, -5));
   	glUniformMatrix4fv(tex_prog->getUniform("M"), 1, GL_FALSE, value_ptr(M->topMatrix()));
   M->popMatrix();

   glUniform1i(tex_prog->getUniform("texBuf"), 0);
   glEnableVertexAttribArray(0);
   glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

   /*glEnableVertexAttribArray(1);
   glBindBuffer(GL_ARRAY_BUFFER, quad_texturebuffer);
   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0);
*/
   glDrawArrays(GL_TRIANGLES, 0, 6);
   glDisableVertexAttribArray(0);
   //glDisableVertexAttribArray(1);
   
   P->popMatrix();
   V->popMatrix();
   tex_prog->unbind();

}

static void setMaterial(int i) {
   int m = i % 5;
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
      case 3: //ruby
         glUniform3f(prog->getUniform("ka"), 0.1745, 0.01175, 0.01175);
         glUniform3f(prog->getUniform("kd"), 0.61424, 0.04136, 0.04136);
         glUniform3f(prog->getUniform("ks"), 0.727811, 0.626959, 0.626959);
         glUniform1f(prog->getUniform("shine"), 76.8);      
         break;
      case 4: //turqouise
         glUniform3f(prog->getUniform("ka"), 0.1, 0.018725, 0.01745);
         glUniform3f(prog->getUniform("kd"), 0.396, 0.74151, 0.69102);
         glUniform3f(prog->getUniform("ks"), 0.297254, 0.30829, 0.306678);
         glUniform1f(prog->getUniform("shine"), 12.8);      
         break;
   }
}

static void drawScene(float aspect, vec3 eyePt, vec3 look, vec3 up) {

   // Create the matrix stacks - please leave these alone for now
   auto P = make_shared<MatrixStack>();
   auto M = make_shared<MatrixStack>();
   auto V = make_shared<MatrixStack>();
   // Apply perspective projection.
   P->pushMatrix();
   P->perspective(45.0f, aspect, 0.01f, 100.0f);

   V->pushMatrix();
   V->lookAt(eyePt, look, up);

	prog->bind();
	glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, value_ptr(P->topMatrix()));
	glUniformMatrix4fv(prog->getUniform("V"), 1, GL_FALSE, value_ptr(V->topMatrix()));
   glUniform3f(prog->getUniform("IL"), 1.0, 1.0, 1.0);
   glUniform3f(prog->getUniform("light"), -2.0+light_trans, 2.0, 0.0);

   // put all dummy objects in world
   for (int i = 0; i < 25; i++) {
      setMaterial((material+i)%4);
      M->pushMatrix();
         M->loadIdentity();
         M->translate(vec3(positions[i][0], positions[i][1], positions[i][2]));
         M->rotate(M_PI/2.0+g_rotate, vec3(0, 1, 0));
	  	   M->rotate(-1.65, vec3(1, 0, 0));
	  	   M->scale(g_scale);
	  	   M->translate(g_trans);
	  	   glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(M->topMatrix()));

		   //iterate through all the shapes and draw them
		   for (int i=0; i < AllShapes.size(); i++) {		
	  		   AllShapes[i]->draw(prog);
		   }
      M->popMatrix();
   }

   // print all nefertiti objects in world
   for (int i = 0; i < 25; i++) {
      setMaterial((material+i)%4);
      M->pushMatrix();
         M->loadIdentity();
         M->translate(vec3(positions2[i][0], positions2[i][1], positions2[i][2]));
         M->scale(0.7);
	  	   M->translate(vec3(-0.9, 0.0, 0.0));
         M->rotate(radians(-90.0f), vec3(1, 0, 0));
	  	   glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(M->topMatrix()));
         shape->draw(prog);
      M->popMatrix();
   }

   // draw cube - turquiose ground
   setMaterial(material+4);
   M->pushMatrix();
      M->loadIdentity();
      M->translate(vec3(0.0, 27.0, 8.0));
      M->scale(20);
      M->translate(vec3(6.2, -2.4, 88));
      M->translate(g_trans);
      glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(M->topMatrix()));
      cube->draw(prog);

   M->popMatrix();

   // Pop matrix stacks.
   P->popMatrix();
   V->popMatrix();
}

static void render()
{
	// Get current frame buffer size.
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

   g_rotate += 0.01;

	//Use the matrix stack for Lab 6
   float aspect = width/(float)height;
   
   // draw scene for portal
   prog->bind();

   // bind fbo for portal view
   glBindFramebuffer(GL_FRAMEBUFFER, frameBuf);
	// Clear framebuffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   drawScene(aspect, portalEye, portalLookAt, upV);
   
   prog->unbind();

   if (FirstTime) {
      assert(GLTextureWriter::WriteImage(texBuf, "texture.png"));
      FirstTime = 0;
   }

   // draw scene for view
   prog->bind();

   // bind fbo back to default screen
   glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// Clear framebuffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   //redefine LookAt angle
   LookAt.x = eye.x + (1.0 * cos(alpha) * cos(beta));
   LookAt.y = eye.y + (1.0 * sin(alpha));
   LookAt.z = eye.z + (1.0 * cos(alpha) * sin(beta));

   //update view vectors
   view = LookAt - eye;
   w = -1.0f * (view/length(view));
   u = normalize(cross(upV, w));
   v = normalize(cross(w, u));
 
   drawScene(aspect, eye, LookAt, upV);
   
   prog->unbind();

   // input portal into scene
   ProcessImage(texBuf, aspect);
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
	window = glfwCreateWindow(800, 800, "Ryan Blair", NULL, NULL);
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
   //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Set keyboard callback.
	glfwSetKeyCallback(window, key_callback);
   //set the mouse call back
   glfwSetMouseButtonCallback(window, mouse_callback);
   //set the mouse call back
   glfwSetCursorPosCallback(window, cursor_position_callback);
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
