#include <stdio.h>

typedef struct {
   double length, width, height;
} Cuboid;

double getLength();
double getWidth();
double getHeight();
Cuboid makeCuboid(double length, double width, double height);
void showResults(Cuboid cuboid);

int main() {
   double width, height, length;
   
   length = getLength();
   width = getWidth();
   height = getHeight();
   
   showResults(makeCuboid(length, width, height));
   
   return 0; 
}

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

void showResults(Cuboid cuboid) {
   double volume, surfArea;

   volume = calcVolume(cuboid);
   surfArea = calcSurfaceArea(cuboid);

   printf("V=%.2f SA=%.2f (Cuboid: L=%.2f W=%.2f H=%.2f)\n", volume, 
      surfArea, cuboid.length, cuboid.width, cuboid.height);
}
