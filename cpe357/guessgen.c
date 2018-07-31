#include <stdio.h>

int main() {
   char a = 'A';
   int i, j, k, l;
 
   for (i = 0; i < 6; i++) {
      for (j = 0; j < 6; j++) {
         for (k = 0; k < 6; k++) {
            for (l = 0; l < 6; l++) {
               printf("%c%c%c%c\n", a + i, a + j, a + k, a + l);
            }
         }
      }
   }

   return 0;
}
