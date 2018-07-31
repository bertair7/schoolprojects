#ifndef CUBOID_H
   #define CUBOID_H

   typedef struct {
      double length, width, height;
   } Cuboid;

   Cuboid makeCuboid(double length, double width, double height);
   double calcVolume(Cuboid cuboid);
   double calcSurfaceArea(Cuboid cuboid);

#endif
