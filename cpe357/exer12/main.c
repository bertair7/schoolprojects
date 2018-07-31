/*
 * Provoided source for Exercise 12: getWord.
 *
 *   !!! DO NOT MODIFY !!!
 *
 * You must use this main in your project solution. Read the provided header
 * file (getWord.h) for the details of the function you must write.
 */
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "memmon.h"
#include "getWord.h"

static void printWord(const char *word, unsigned wordLength)
{
   int i;

   /* For readability, this program limits each line to 72 characters max */
   for (i = 0; i < wordLength && i < 72; i++)
   {
      if (isprint(word[i]))
         printf("%c", word[i]);
      else
         printf("%c", UCHAR_MAX);
   }
   
   if (wordLength)
      printf("\n");
}

/*
 * Required main for Exercise 12: getWord 
 *
 * This program reads files from stdin by calling getWord (the function you
 * must write). The getWord function returns each word found in the file in
 * its own dynamically allocated and correctly sized memory buffer. The
 * "words" and printed and memmon is called at the end to verify that the
 * correct amount of memory was allocated.
 */
int main()
{
   char *word = NULL;
   unsigned wordLength = 0;

   /* Call getWord and print the words, until done... */
   while(EOF != getWord(&word, &wordLength, stdin, "stdin"))
      printWord(word, wordLength);

   /* Print the last word returned with the EOF */
   printWord(word, wordLength);

   /* This should be the sum of the number of bytes in all words */
   printf("\nCurrently allocated memory: %u bytes\n\n", memCurrent());

   return EXIT_SUCCESS;
}
