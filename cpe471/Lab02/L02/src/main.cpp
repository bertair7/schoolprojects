#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Image.h"

// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
using namespace std;

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

void findBoundingBox(int vax, int vay, int vbx, int vby, int vcx, int vcy, BoundingBox *box);
void inTriangle(float vax, float vay, float vbx, float vby, float vcx, float vcy, float x, float y, BaryCoor *b);

int main(int argc, char **argv)
{
	if(argc < 10) {
		cout << "Usage: L02 filename width height x0 y0 r0 g0 b0 x1 y1 r1 g1 b1 x2 y2 r2 g2 b2" << endl;
		return 0;
	}
	// Output filename
	string filename(argv[1]);
	// Width of image
	int width = atoi(argv[2]);
	// Height of image
	int height = atoi(argv[3]);

   int vax = atoi(argv[4]);
   int vay = atoi(argv[5]);
   int var = atoi(argv[6]);
   int vag = atoi(argv[7]);
   int vab = atoi(argv[8]);

   int vbx = atoi(argv[9]);
   int vby = atoi(argv[10]);
   int vbr = atoi(argv[11]);
   int vbg = atoi(argv[12]);
   int vbb = atoi(argv[13]);

   int vcx = atoi(argv[14]);
   int vcy = atoi(argv[15]);
   int vcr = atoi(argv[16]);
   int vcg = atoi(argv[17]);
   int vcb = atoi(argv[18]);

   BoundingBox box;
   BaryCoor b;

   // find bounding box
   findBoundingBox(vax, vay, vbx, vby, vcx, vcy, &box);

	// Create the image. We're using a `shared_ptr`, a C++11 feature.
	auto image = make_shared<Image>(width, height);
	// Draw a rectangle
	//for(int y = 10; y < 20; ++y) {
	//	for(int x = 20; x < 40; ++x) {
	//		unsigned char r = 255;
	//		unsigned char g = 0;
	//		unsigned char b = 0;
	//		image->setPixel(x, y, r, g, b);
	//	}
	//}

   // draw triangle
   float zero = -0.00001;
   float one = 1.00001;

   for (int y = box.ymin; y <= box.ymax; y++)
   {
      for (int x = box.xmin; x <= box.xmax; x++)
      {
			inTriangle((float)vax, (float)vay, (float)vbx, (float)vby, (float)vcx, (float)vcy, (float)x, (float)y, &b);
         if (zero <= b.alpha && zero <= b.beta && zero <= b.gamma && b.alpha <= one && b.beta <= one && b.gamma <= one)
         {
            int red = b.alpha*var + b.beta*vbr + b.gamma*vcr;
            int green = b.alpha*vag + b.beta*vbg + b.gamma*vcg;
            int blue = b.alpha*vab + b.beta*vbb + b.gamma*vcb;
            image->setPixel(x, y, red, green, blue);
		   }
      }
   }

   // draw vertices
   image->setPixel(vax, vay, 255, 255, 255);
   image->setPixel(vbx, vby, 255, 255, 255);
   image->setPixel(vcx, vcy, 255, 255, 255);

	// Write image to file
	image->writeToFile(filename);
	return 0;
}

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

void inTriangle(float vax, float vay, float vbx, float vby, float vcx, float vcy, float x, float y, BaryCoor *b)
{
	b->beta = (float)(((vax-vcx)*(y-vcy) - (vay-vcy)*(x-vcx)) / ((vbx-vax)*(vcy-vay) - (vby-vay)*(vcx-vax)));
	b->gamma = (float)(((vbx-vax)*(y-vay) - (vby-vay)*(x-vax)) / ((vbx-vax)*(vcy-vay) - (vby-vay)*(vcx-vax)));
   b->alpha = 1.0 - b->beta - b->gamma;

}
