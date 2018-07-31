#include <limits.h>
#include <float.h>
#include <stdio.h>

int main() {
   printf("%12s: %20d (%s)\n", "CHAR_BIT", CHAR_BIT, "N/A");
   printf("%12s: %20d (%d byte)\n", "CHAR_MIN", CHAR_MIN, (int)(sizeof(char)));
   printf("%12s: %20d (%d byte)\n", "CHAR_MAX", CHAR_MAX, (int)(sizeof(char)));
   printf("%12s: %20d (%d byte)\n", "SCHAR_MIN", SCHAR_MIN, 
      (int)(sizeof(signed char)));
   printf("%12s: %20d (%d byte)\n", "SCHAR_MAX", SCHAR_MAX, 
      (int)(sizeof(signed char)));
   printf("%12s: %20d (%d byte)\n\n", "UCHAR_MAX", UCHAR_MAX, 
      (int)(sizeof(unsigned char)));
 
   printf("%12s: %20d (%d bytes)\n", "SHRT_MIN", SHRT_MIN, 
      (int)(sizeof(short)));
   printf("%12s: %20d (%d bytes)\n", "SHRT_MAX", SHRT_MAX, 
      (int)(sizeof(short)));
   printf("%12s: %20d (%d bytes)\n\n", "USHRT_MAX", USHRT_MAX, 
      (int)(sizeof(unsigned short)));

   printf("%12s: %20d (%d bytes)\n", "INT_MIN", INT_MIN, (int)(sizeof(int)));
   printf("%12s: %20d (%d bytes)\n", "INT_MAX", INT_MAX, (int)(sizeof(int)));
   printf("%12s: %20u (%d bytes)\n\n", "UINT_MAX", UINT_MAX, 
      (int)(sizeof(unsigned int)));

   printf("%12s: %20ld (%d bytes)\n", "LONG_MIN", LONG_MIN, 
      (int)(sizeof(long)));
   printf("%12s: %20ld (%d bytes)\n", "LONG_MAX", LONG_MAX, 
      (int)(sizeof(long)));
   printf("%12s: %20lu (%d bytes)\n\n", "ULONG_MAX", ULONG_MAX, 
      (int)(sizeof(unsigned long)));

   printf("%12s: %20g (%s)\n", "FLT_EPSILON", FLT_EPSILON, "N/A");
   printf("%12s: %20g (%d bytes)\n", "FLT_MIN", FLT_MIN, (int)(sizeof(float)));
   printf("%12s: %20g (%d bytes)\n\n", "FLT_MAX", FLT_MAX, 
      (int)(sizeof(float)));

   printf("%12s: %20g (%s)\n", "DBL_EPSILON", DBL_EPSILON, "N/A");
   printf("%12s: %20g (%d bytes)\n", "DBL_MIN", DBL_MIN, (int)(sizeof(double)));
   printf("%12s: %20g (%d bytes)\n\n", "DBL_MAX", DBL_MAX, 
      (int)(sizeof(double)));

   return 0;
}
