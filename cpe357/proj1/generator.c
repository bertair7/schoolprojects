#include "generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findChar(char test, char *guess, char *answer);

Pattern makePattern(int seed, char max, int positions, long guess) {
   char temp[9], tempChar;
   int i;
   Pattern pattern;

   /* insert pattern creating algorithm here */
   srand(seed);
   
   for (i = 0; i < positions; i++) {
      tempChar = rand() % ((int)max - 65 + 1) + 65;
      temp[i] = tempChar;
   }
   temp[positions] = '\0';

   strcpy(pattern.answer, temp);
   pattern.numLetters = positions;
   pattern.maxLetter = max;
   pattern.guesses = guess;
   return pattern;
}

int checkIfCorrect(Pattern pattern, char *guess) {
   if (strcmp(pattern.answer, guess) == 0)
      return 1;
   return 0;
}

int determineExact(Pattern pattern, char *guess) {
   int exact = 0, i;
   
   for (i = 0; i < pattern.numLetters; i++) {
      if (pattern.answer[i] == guess[i]) 
         exact++;
   }
   return exact;
}

int determineInexact(Pattern pattern, char *guess) {
   int inexact = 0, i;
   char test, testedChar[9];
   
   strcpy(testedChar, pattern.answer);
   for (i = 0; i < pattern.numLetters; i++) {
      test = guess[i];
      if (strchr(testedChar, test) && pattern.answer[i] != guess[i]) {
         inexact += findChar(guess[i], guess, testedChar);
      }
   }
   return inexact;
}

int findChar(char test, char *guess, char *answer) {
   int i;
   i = 0;

   while (answer[i] != '\0') { 
      if (answer[i] == test && answer[i] != guess[i]) {
         answer[i] = 'a';
         return 1;
      }
      i++;
   }
   return 0;
}
