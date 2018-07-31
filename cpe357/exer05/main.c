#include "ui.h"
#include "cuboid.h"

int main() {
   double width, height, length;
   
   length = getLength();
   width = getWidth();
   height = getHeight();
   
   showResults(makeCuboid(length, width, height));
   
   return 0; 
}
