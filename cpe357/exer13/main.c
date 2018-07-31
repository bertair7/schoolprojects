/*
 * Provided source - DO NOT MODIFY !!!
 */
#include <stdio.h>
#include <stdlib.h>
#include "memmon.h" 

/* 
 * Prototype of the function you must write in a separate source file. Note
 * that you may write additional helper functions for this function in the 
 * source file(s) you decide to create for this exercise.
 */
void sortPeople(const char *inputFileName, const char *outputFileName);

#define PGM_NAME "sortPeople"

static int checkArgs(int argc, char *argv[])
{
   int outOfMemory;

   if (argc != 4 || 1 != sscanf(argv[1], "%d", &outOfMemory))
   {
      fprintf(stderr, "Usage: %s memmonFlag(0|!0) inFileName outFileName\n",
         PGM_NAME);
      exit(EXIT_FAILURE);
   }

   return outOfMemory;
}

int main(int argc, char *argv[])
{
   /* Check args and set memmon's state */
   memSetOutOfMemory(checkArgs(argc, argv));

   /* Call the function you must write */
   sortPeople(argv[2], argv[3]);

   /* Report the memory usage to see if it matches expectations */
   printf("\nNumber of memory allocations: %d\n", memAllocs());
   printf("Number of memory frees      : %d\n", memFrees());
   printf("Peak memory allocation      : %u\n", memPeak());
   printf("Current memory allocation   : %u\n\n", memCurrent());

   return EXIT_SUCCESS;
}
