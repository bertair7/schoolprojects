#include <stdio.h>

double getLength();
double getWidth();
double getHeight();
void showResults(double length, double width, double height);

int main() {
   double width, height, length;

   length = getLength();
   width = getWidth();
   height = getHeight();
   
   showResults(length, width, height);
   
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

double calcVolume(double length, double width, double height) {
   return width * height * length;
}

double calcSurfaceArea(double length, double width, double height) {
   return 2*(width*height) + 2*(width*length) + 2*(height*length);
}

void showResults(double length, double width, double height) {
   double volume, surfArea;

   volume = calcVolume(length, width, height);
   surfArea = calcSurfaceArea(length, width, height);

   printf("V=%.2f SA=%.2f (Cuboid: L=%.2f W=%.2f H=%.2f)\n", volume, 
      surfArea, length, width, height);
}
