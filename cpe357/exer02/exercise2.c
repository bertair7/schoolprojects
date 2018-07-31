#include <stdio.h>

int main() {
   double width, height, length, volume, surfArea;

   printf("Enter the length of the cuboid: ");
   scanf("%lf", &length);  
  
   printf("Enter the  width of the cuboid: ");
   scanf("%lf", &width);  
  
   printf("Enter the height of the cuboid: ");
   scanf("%lf", &height);  

   volume = width * height * length;
   surfArea = 2*(width*height) + 2*(width*length) + 2*(height*length);

   printf("V=%.2f SA=%.2f (Cuboid: L=%.2f W=%.2f H=%.2f)\n", volume, 
      surfArea, length, width, height);

   return 0; 
}
