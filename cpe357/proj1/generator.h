#ifndef GENERATOR_H
   #define GENERATOR_H

   typedef struct {
      char answer[9];
      int numLetters;
      char maxLetter;
      long guesses;
   } Pattern;

   Pattern makePattern(int seed, char max, int positions, long guess);
   int checkIfCorrect(Pattern pattern, char *guess);
   int determineExact(Pattern pattern, char *guess);
   int determineInexact(Pattern pattern, char *guess);
   
#endif
