#include "cuboid.h"
#include <stdio.h>

Cuboid makeCuboid(double length, double width, double height) {
   Cuboid cuboid;

   cuboid.length = length;
   cuboid.width = width;
   cuboid.height = height;

   return cuboid;
}

double calcVolume(Cuboid cuboid) {
   return cuboid.width * cuboid.height * cuboid.length;
}

double calcSurfaceArea(Cuboid cuboid) {
   return 2*(cuboid.width*cuboid.height) + 2*(cuboid.width*cuboid.length) 
      + 2*(cuboid.height*cuboid.length);
}
