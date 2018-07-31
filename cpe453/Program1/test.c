#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
   /*char *debug = getenv("DEBUG_MALLOC");
   puts(debug);*/

   char *s;
   s = strdup("Trial"); /* should call malloc() implicitly */
   puts(s);
   free(s);
   
   s = strdup("Next one");
   puts(s);
   free(s);
  
   return 0;
}
