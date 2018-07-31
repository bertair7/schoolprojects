#include <stdio.h>
#include <stdlib.h>
#include "memmon.h"

#define MAX_PATH 4096

/* Prototype of function you must write in a separate file
 */
int getLine(char **line, FILE *file);

/*
 * Provided test driver - DO NOT MODIFY !!!
 *
 * For simplicity, this test driver expects perfect user input.
 */
int main()
{
   int outOfMemory;
   char fileName[MAX_PATH];
   char *line;
   FILE *file;

   printf("Set out of memory (0|!0)? ");
   scanf("%d", &outOfMemory);
   memSetOutOfMemory(outOfMemory);

   printf("File name: ");
   scanf("%s", fileName);
   file = fopen(fileName, "r");

   /* A loop calling the function you must write in a SEPARATE file */
   while(EOF != getLine(&line, file))
   {
      printf("Line: %s\n", line);
      printf("Current allocation: %u\n\n", memCurrent());
      free(line);
   }

   printf("Peak memory allocation: %u\n", memPeak());
   return 0;
}
