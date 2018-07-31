#include <stdio.h>
#include <stdlib.h>
#include "exam1p3.h"

/*
 * Provided source for Exam 1, Problem 3 - DO NOT MODIFY !!!
 * 
 * Note that you are not required to turn in this provided file but it will
 * not be a problem if you do.
 */

/*
 * Maximum number of values supported by this test driver.
 */ 
#define MAX_VALUES 100

int main()
{
   unsigned numberOfValues;
   int values[MAX_VALUES];
   int i;
   Results results;

   /* Prompt and read the array to check */
   printf("Enter the number of values in the sequence: ");
   scanf("%u", &numberOfValues);

   for (i = 0; i < numberOfValues; i++)
      scanf("%d", &values[i]);

   /* Call the function you must write in a different source file */
   results = findSequence(values, numberOfValues);

   /* Display the results */
   printf("Start  of sequence is %u\n", results.start);
   printf("Length of sequence is %u\n", results.length);

   return EXIT_SUCCESS;
}
