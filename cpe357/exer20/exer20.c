#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void getHex(char *operator, unsigned int *hex) {
   int flag = 0, i = 0;

   while (!flag) {
      printf("Enter RHS for the %s operator in hex: ", operator);
      if (1 == scanf("%x", hex))
         flag = 1;
      else {
         printf("RHS must be a value in hex, please try again\n");
         while (getc(stdin) != '\n')
            i++;
      }
   }
}

static void getDec(char *operator, int *dec) {
   int flag = 0, i = 0;

   while (!flag) {
      printf("Enter RHS for the %s operator in decimal: ", operator);
      if (1 == scanf("%d", dec))
         flag = 1;
      else {
         printf("RHS must be an unsigned value in decimal, please try again");
         printf("\n");
         while (getc(stdin) != '\n')
            i++;
      }
   }
}

int main(void) {
   unsigned int result = 0, inputHex;
   int inputNum, flag = 1;
   char inputSign[5];

   while (1) {
      if (flag)
         printf("\nCurrent value: 0x%08X\n", result);
      printf("Enter bitwise operator (or \"quit\"): ");
      scanf("%s", inputSign);

      if (strcmp(inputSign, "&") == 0) {
         getHex(inputSign, &inputHex);
         printf("0x%08X & 0x%08X is ", result, inputHex);
         result = result & inputHex;
         printf("0x%08X\n", result);
         flag = 1;
      }
      else if (strcmp(inputSign, "|") == 0) {
         getHex(inputSign, &inputHex);
         printf("0x%08X | 0x%08X is ", result, inputHex);
         result = result | inputHex;
         printf("0x%08X\n", result);
         flag = 1;
      }
      else if (strcmp(inputSign, "^") == 0) {
         getHex(inputSign, &inputHex);
         printf("0x%08X ^ 0x%08X is ", result, inputHex);
         result = result ^ inputHex;
         printf("0x%08X\n", result);
         flag = 1;
      }
      else if (strcmp(inputSign, "<<") == 0) {
         getDec(inputSign, &inputNum);
         printf("0x%08X << %d is ", result, inputNum);
         result = result << inputNum;
         printf("0x%08X\n", result);
         flag = 1;
      }
      else if (strcmp(inputSign, ">>") == 0) {
         getDec(inputSign, &inputNum);
         printf("0x%08X >> %d is ", result, inputNum);
         result = result >> inputNum;
         printf("0x%08X\n", result);
         flag = 1;
      }
      else if (strcmp(inputSign, "~") == 0) {
         printf("~0x%08X is ", result);
         result = ~result;
         printf("0x%08X\n", result);
         flag = 1;
      }
      else if (strcmp(inputSign, "quit") == 0) {
         break;
      }
      else {
         printf("Unrecognized operator '%s', please try again\n", inputSign);
         flag = 0;
      }
   }

   return EXIT_SUCCESS;
}
