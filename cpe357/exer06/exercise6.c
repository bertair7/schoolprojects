#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printInt(int number, int input);
void printDouble(int number, double input);
void printChar(int number, char input);
void printString(int number, char *input);

int main(int argc, char *argv[]) {
   int i, checkI;
   double checkD;
   char checkC;

   if (argc < 2) {
      fprintf(stderr, "Usage: dataTyper argument [argument ...]\n");
      exit(EXIT_FAILURE);
   }
   else {
      for (i = 1; i < argc; i++) {
         if (sscanf(argv[i], "%d", &checkI) && strchr(argv[i], '.') == NULL) 
            printInt(i, checkI);
         else if (sscanf(argv[i], "%lf", &checkD))
            printDouble(i, checkD);
         else if (sscanf(argv[i], "%c", &checkC)) {
            if (strlen(argv[i]) == 1)
               printChar(i, checkC);
            else
               printString(i, argv[i]);
         }
      }
   }
   return 0;
}

void printInt(int number, int input) {
   printf("   Argument %d is an int, its value is %d\n", number, input);
}

void printDouble(int number, double input) {
   printf("   Argument %d is a double, its value is %.6f\n", number, input);
}

void printChar(int number, char input) {
   printf("   Argument %d is a char, its value is %c\n", number, input);
}

void printString(int number, char *input) {
   printf("   Argument %d is a string, its value is %s\n", number, input);
}
