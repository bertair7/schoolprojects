#include "generator.h"
#include "ui.h"
#include <stdio.h>

int getSeed() {
   int seed;
   
   while (1) {
      printf("Enter the seed for random number generation: ");
      if (scanf("%d", &seed) > 0) {
         clearBuffer();
         return seed;
      }
      else {
         clearBuffer();
         printf("Seed must be an integer value, please try again\n");
      }
   }  
}

char getMaxLetter() {
   char max;

   while (1) {
      printf("Enter the maximum letter for the game (A-Z): ");
      if ((scanf(" %c", &max) > 0) && max >= 'A' && max <= 'Z') {
         clearBuffer();
         return max;
      }
      else {
         clearBuffer();
         printf("The letter must be an uppercase A-Z, please try again\n");
      }
   }  
}

int getPositions() {
   int positions;

   while (1) {
      printf("Enter the number of positions for the game (1-8): ");
      if ((scanf("%d", &positions) > 0) && positions > 0 && positions < 9) {
         clearBuffer();
         return positions;
      }
      else {
         clearBuffer();
         printf("The number of positions must be 1-8, please try again\n");
      }
   }  
}

long getGuesses() {
   long guesses;

   while (1) {
      printf("Enter the number of guesses allowed for the game: ");
      if ((scanf("%ld", &guesses) > 0) && guesses > 0) {
         clearBuffer();
         return guesses;
      }
      else {
         clearBuffer();
         printf("The number guesses must be a positive integer, ");
         printf("please try again\n");
      }
   }  
}

void clearBuffer() {
   scanf("%*[^\n]");
   scanf("%*c");
}
