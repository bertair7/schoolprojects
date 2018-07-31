#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "ui.h"
#include "generator.h"

int runGame(Pattern pattern);

int main(int argc, char *argv[]) {
   int seed, positions, result;
   long guesses;
   char max;
   char check[] = "-show";
   Pattern pattern;

   if (argc != 1 && (argc > 2 || strcmp(argv[1], check) != 0)) {
      fprintf(stderr, "Usage: mastermind [-show]\n");
      exit(EXIT_FAILURE);
   }

   seed = getSeed();
   max = getMaxLetter();
   positions = getPositions();
   guesses = getGuesses();

   pattern = makePattern(seed, max, positions, guesses);
   
   if (argc == 2)
      printf("Initialized Game Board: %s\n", pattern.answer);

   result = runGame(pattern);
   if (!result)
      printf("\nGame over, you ran out of guesses. Better luck next time!\n");
   else
      printf("\nWow, you won in %d guesses - well done!\n", result);

   return 0;
}

int determineCorrectGuess(Pattern pattern, char *guess) {
   int exact, inexact; 
   if (checkIfCorrect(pattern, guess)) {
      return 1;
   }
   else {
      exact = determineExact(pattern, guess);
      inexact = determineInexact(pattern, guess);
      printf("Nope, %d exact guesses and %d inexact guesses\n", exact,
         inexact);
   }
   return 0;
}

int determineValidGuess(Pattern pattern, char *guess) {
   int i;
   char c;

   for (i = 0; i < pattern.numLetters; i++) {
      c = guess[i];
      if (c < 'A' || c > pattern.maxLetter)
         return 0;
   }

   return 1;
}

char *getUserInput(Pattern pattern) {
   char guess[9], in, *final;
   int i = 0;

   final = (char *)malloc(pattern.numLetters * sizeof(char));

   while (i < pattern.numLetters) {
      scanf(" %c", &in);
      if (!isspace(in)) {
         guess[i] = in;
         i++;
      }
   }
   clearBuffer();
   guess[pattern.numLetters] = '\0';

   strcpy(final, guess);
   return final;
}

int runGame(Pattern pattern) {
   int totalGuess, win;
   char *userGuess;

   totalGuess = 1;
   win = 0;
   userGuess = (char *)malloc(pattern.numLetters * sizeof(char));

   while (totalGuess <= pattern.guesses && !win) {
      printf("\nEnter guess %d: ", totalGuess);
      strcpy(userGuess, getUserInput(pattern));
      if (determineValidGuess(pattern, userGuess)) {
         if (determineCorrectGuess(pattern, userGuess)) {
            win = 1;
            break;
         }
         else
            totalGuess++;
      }
      else {
         printf("Invalid guess, please try again\n");
      }
   }

   if (win)
      return totalGuess;
   return 0;
}
