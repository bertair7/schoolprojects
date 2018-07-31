#include "cuboid.h"
#include <stdio.h>

double getLength() {
   double length;

   printf("Enter the length of the cuboid: ");
   scanf("%lf", &length);  
   return length;
}

double getWidth() {
   double width;

   printf("Enter the  width of the cuboid: ");
   scanf("%lf", &width);  
   return width;
}

double getHeight() {
   double height;

   printf("Enter the height of the cuboid: ");
   scanf("%lf", &height);  
   return height;
}

void showResults(Cuboid cuboid) {
   double volume, surfArea;

   volume = calcVolume(cuboid);
   surfArea = calcSurfaceArea(cuboid);

   printf("V=%.2f SA=%.2f (Cuboid: L=%.2f W=%.2f H=%.2f)\n", volume, 
      surfArea, cuboid.length, cuboid.width, cuboid.height);
}
