#include <stdio.h>

int main (int argc, char *argv[]) {
   int limit, i, input, total, avg;

   printf("Enter the number of values to average: ");
   scanf("%d", &limit);
   total = 0;

   for (i = 0; i < limit; i++) {
      printf("Enter value %d: ", i+1);
      scanf("%d", &input);
      total += input;
   }

   avg = total / input;

   printf("The average is %d\n", avg);

   return 0;
}
