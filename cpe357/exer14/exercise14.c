#include <assert.h>
#include <math.h>

int sphereVolume(double r, double pi) {
   double volume;
 
   assert (r > 0);

   volume = pi * pow(r, 3) * 4 / 3;

   return (int)volume;
}
