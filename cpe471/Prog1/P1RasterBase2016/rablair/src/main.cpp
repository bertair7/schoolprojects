/* Release code for program 1 CPE 471 Fall 2016 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "Image.h"

// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
using namespace std;

int g_width, g_height;

typedef struct {
   int xmin;
   int xmax;
   int ymin;
   int ymax;
} BoundingBox;

typedef struct {
   float alpha;
   float beta;
   float gamma;
} BaryCoor;

void findBoundingBox(int vax, int vay, int vbx, int vby, int vcx, int vcy, BoundingBox *box) 
{
   if (vax < vbx)
   {   
      if (vbx < vcx)
      {   
         box->xmax = vcx;
         box->xmin = vax;
      }   
      else
      {   
         box->xmax = vbx;
         if (vax < vcx)
         {
            box->xmin = vax;
         }
         else
         {
            box->xmin = vcx;
         }
      }   
   }   
   else
   {   
      if (vax < vcx)
      {   
         box->xmax = vcx;
         box->xmin = vbx;
      }   
      else
      {   
         box->xmax = vax;
         if (vbx < vcx)
         {
            box->xmin = vbx;
         }
         else
         {
            box->xmin = vcx;
         }
      }   
   }   
   if (vay < vby)
   {   
      if (vby < vcy)
      {   
         box->ymax = vcy;
         box->ymin = vay;
      }   
      else
      {   
         box->ymax = vby;
         if (vay < vcy)
         {
            box->ymin = vay;
         }
         else
         {
            box->ymin = vcy;
         }
      }
   }
   else
   {
      if (vay < vcy)
      {
         box->ymax = vcy;
         box->ymin = vby;
      }
      else
      {
         box->ymax = vay;
         if (vby < vcy)
         {
            box->ymin = vby;
         }
         else
         {
            box->ymin = vcy;
         }
      }
   }
}

void inTriangle(float vax, float vay, float vbx, float vby, float vcx, float vcy, float x, float y, BaryCoor *bc) 
{
   bc->beta = (float)(((vax-vcx)*(y-vcy) - (vay-vcy)*(x-vcx)) / ((vbx-vax)*(vcy-vay) - (vby-vay)*(vcx-vax)));
   bc->gamma = (float)(((vbx-vax)*(y-vay) - (vby-vay)*(x-vax)) / ((vbx-vax)*(vcy-vay) - (vby-vay)*(vcx-vax)));
   bc->alpha = 1.0 - bc->beta - bc->gamma;
}

/*
   Helper function you will want all quarter
   Given a vector of shapes which has already been read from an obj file
   resize all vertices to the range [-1, 1]
 */
void resize_obj(std::vector<tinyobj::shape_t> &shapes){
   float minX, minY, minZ;
   float maxX, maxY, maxZ;
   float scaleX, scaleY, scaleZ;
   float shiftX, shiftY, shiftZ;
   float epsilon = 0.001;

   minX = minY = minZ = 1.1754E+38F;
   maxX = maxY = maxZ = -1.1754E+38F;

   //Go through all vertices to determine min and max of each dimension
   for (size_t i = 0; i < shapes.size(); i++) {
      for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
         if(shapes[i].mesh.positions[3*v+0] < minX) minX = shapes[i].mesh.positions[3*v+0];
         if(shapes[i].mesh.positions[3*v+0] > maxX) maxX = shapes[i].mesh.positions[3*v+0];

         if(shapes[i].mesh.positions[3*v+1] < minY) minY = shapes[i].mesh.positions[3*v+1];
         if(shapes[i].mesh.positions[3*v+1] > maxY) maxY = shapes[i].mesh.positions[3*v+1];

         if(shapes[i].mesh.positions[3*v+2] < minZ) minZ = shapes[i].mesh.positions[3*v+2];
         if(shapes[i].mesh.positions[3*v+2] > maxZ) maxZ = shapes[i].mesh.positions[3*v+2];
      }
   }

	//From min and max compute necessary scale and shift for each dimension
   float maxExtent, xExtent, yExtent, zExtent;
   xExtent = maxX-minX;
   yExtent = maxY-minY;
   zExtent = maxZ-minZ;
   if (xExtent >= yExtent && xExtent >= zExtent) {
      maxExtent = xExtent;
   }
   if (yExtent >= xExtent && yExtent >= zExtent) {
      maxExtent = yExtent;
   }
   if (zExtent >= xExtent && zExtent >= yExtent) {
      maxExtent = zExtent;
   }
   scaleX = 2.0 /maxExtent;
   shiftX = minX + (xExtent/ 2.0);
   scaleY = 2.0 / maxExtent;
   shiftY = minY + (yExtent / 2.0);
   scaleZ = 2.0/ maxExtent;
   shiftZ = minZ + (zExtent)/2.0;

   //Go through all verticies shift and scale them
   for (size_t i = 0; i < shapes.size(); i++) {
      for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
         shapes[i].mesh.positions[3*v+0] = (shapes[i].mesh.positions[3*v+0] - shiftX) * scaleX;
         assert(shapes[i].mesh.positions[3*v+0] >= -1.0 - epsilon);
         assert(shapes[i].mesh.positions[3*v+0] <= 1.0 + epsilon);
         shapes[i].mesh.positions[3*v+1] = (shapes[i].mesh.positions[3*v+1] - shiftY) * scaleY;
         assert(shapes[i].mesh.positions[3*v+1] >= -1.0 - epsilon);
         assert(shapes[i].mesh.positions[3*v+1] <= 1.0 + epsilon);
         shapes[i].mesh.positions[3*v+2] = (shapes[i].mesh.positions[3*v+2] - shiftZ) * scaleZ;
         assert(shapes[i].mesh.positions[3*v+2] >= -1.0 - epsilon);
         assert(shapes[i].mesh.positions[3*v+2] <= 1.0 + epsilon);
      }
   }
}

int w2px(float x, float c, float d) {
   return (c * x + d);
}

int w2py(float y, float e, float f) {
   return (e * y + f);
}

int main(int argc, char **argv)
{
	if(argc < 6) {
      cout << "Usage: Assignment1 meshfile imagefile width height col_mode" << endl;
      return 0;
   }
	// OBJ filename
	string meshName(argv[1]);
	string imgName(argv[2]);
   g_width = atoi(argv[3]);
   g_height = atoi(argv[4]);
   int mode = atoi(argv[5]);

   //create an image
	auto image = make_shared<Image>(g_width, g_height);

	// triangle buffer
	vector<unsigned int> triBuf;
	// position buffer
	vector<float> posBuf;
	// Some obj files contain material information.
	// We'll ignore them for this assignment.
	vector<tinyobj::shape_t> shapes; // geometry
	vector<tinyobj::material_t> objMaterials; // material
	string errStr;
	
   bool rc = tinyobj::LoadObj(shapes, objMaterials, errStr, meshName.c_str());
	/* error checking on read */
	if(!rc) {
		cerr << errStr << endl;
	} else {
 		//keep this code to resize your object to be within -1 -> 1
   	resize_obj(shapes); 
		posBuf = shapes[0].mesh.positions;
		triBuf = shapes[0].mesh.indices;
	}
	cout << "Number of vertices: " << posBuf.size()/3 << endl;
	cout << "Number of triangles: " << triBuf.size()/3 << endl;

	//TODO add code to iterate through each triangle and rasterize it 
   BoundingBox box;
   BaryCoor bc;
   float left, right, bot, top, c, d, e, f;
   float curr_z;
   float zero = -0.00001;
   float one = 1.00001;
   vector<vector<float>> zbuff(g_width);
   int triangles = triBuf.size()/3;

   if (g_width > g_height) 
   {
      left = -g_width/g_height;
      right = g_width/g_height;
      bot = -1.0;
      top = 1.0;
   }
   else 
   {
      left = -1.0;
      right = 1.0;
      bot = -g_height/g_width;
      top = g_height/g_width;
   }

   for (int r = 0; r < g_width; r++)
   {
      zbuff[r].resize(g_height);
      for (int s = 0; s < g_height; s++)
      {
         zbuff[r][s] = -100000.0;
      }
   }

   c = (1.0-g_width)/(left-right);
   d = -c*left;
   e = (1.0-g_height)/(bot-top);
   f = -e*bot;

   for (int i = 0; i < triangles; i++) 
   {
      int v1 = triBuf[i*3];
      int v2 = triBuf[i*3+1];
      int v3 = triBuf[i*3+2];

      int v1x = w2px(posBuf[v1*3], c, d);
      int v1y = w2py(posBuf[v1*3+1], e, f);
      float v1z = posBuf[v1*3+2];

      int v2x = w2px(posBuf[v2*3], c, d);
      int v2y = w2py(posBuf[v2*3+1], e, f);
      float v2z = posBuf[v2*3+2];

      int v3x = w2px(posBuf[v3*3], c, d);
      int v3y = w2py(posBuf[v3*3+1], e, f);
      float v3z = posBuf[v3*3+2];

      findBoundingBox(v1x, v1y, v2x, v2y, v3x, v3y, &box);

      for (int y = box.ymin; y < box.ymax; y++) 
      {
         for (int x = box.xmin; x < box.xmax; x++) 
         {
            inTriangle((float)v1x, (float)v1y, (float)v2x, (float)v2y, (float)v3x, (float)v3y, (float)x, (float)y, &bc);
            if (zero <= bc.alpha && zero <= bc.beta && zero <= bc.gamma && bc.alpha <= one && bc.beta <= one && bc.gamma <= one)
            {
               curr_z = bc.alpha*v1z + bc.beta*v2z + bc.gamma*v3z;
               if (zbuff[x][y] < curr_z) 
               {
                  zbuff[x][y] = curr_z;
                  if (mode == 1)
                  {
                     int red = (curr_z+1.0)*128.0;
                     image->setPixel(x, y, red, 0, 0);
                  }
                  else
                  {
                     float yshift = (v1y*bc.alpha + v2y*bc.beta + v3y*bc.gamma)/g_height;
                     image->setPixel(x, y, 255*(1-yshift), 0, 255*yshift);
                  }
               }
            }
         }
      }
   }
   
	//write out the image
   image->writeToFile(imgName);

	return 0;
}