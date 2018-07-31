#include <stdio.h>

int input; 
void countBackwardFrom(int x);
void countForwardTo(int x);

int main() {
   printf("Insert an integer: ");
   scanf(" %d", &input);
   printf("Backward: ");
   countBackwardFrom(input);
   printf("\nForward: ");
   countForwardTo(input);
   printf("\n");
   return 0;
}

/**
* This function counts backward from x to 1 by one.
* For example, calling this function with a value of 5 should
* result in the following output:
* 5, 4, 3, 2, 1
*/
void countBackwardFrom(int x) {
   if(x <= 1)
      printf("%d ", 1);
   else {
      printf("%d ", x);
      countBackwardFrom(x-1);
   }
}

/**
* This function counts from one to x by one.
* For example, calling this method with a value of 5 should 
* result in the following output:
* 1, 2, 3, 4, 5
*/
void countForwardTo(int x) {
   if(x <= 1) 
      printf("%d ", x);
   else {
      countForwardTo(x-1);
      printf("%d ", x);
   }
}
