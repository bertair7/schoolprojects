#include "exam1p3.h"

Results findSequence(int array[], int size) {
   int tempInd, tempLen, i;
   unsigned bestInd, bestLen;
   Results result;

   tempInd = 0;
   tempLen = 1;
   bestInd = 0;
   bestLen = 1;

   for (i = 0; i < size-1; i++) {
      if (array[i] < array[i+1]) {
         tempLen++;
      }
      else {
         if (tempLen > bestLen) {
            bestInd = tempInd;
            bestLen = tempLen;
            tempInd = i+1;
            tempLen = 1;
         }
         else {
            tempInd = i+1;
            tempLen = 1;
         }
      }
   }
   
   if (tempLen > bestLen) {
      bestInd = tempInd;
      bestLen = tempLen;
   }

   result.start = bestInd;
   result.length = bestLen;

   return result;
}
