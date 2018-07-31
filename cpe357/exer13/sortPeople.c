#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "memmon.h"

#define MAXFIRST 21
#define MAXLAST 31
#define MAXSTATE 3

typedef struct {
   char firstName[MAXFIRST];
   char lastName[MAXLAST];
   char state[MAXSTATE];
   unsigned short age;
} Person;

FILE *checkFile(const char *inFile) {
   FILE *input;

   input = fopen(inFile, "r");
   if (input == NULL) {
      fprintf(stderr, "%s: ", inFile);
      perror("");
      exit(EXIT_FAILURE);
   }
   return input;
}

Person newPerson(char *first, char *last, char *state, unsigned short age) {
   Person person;

   strcpy(person.firstName, first);
   person.firstName[MAXFIRST] = 0;
   strcpy(person.lastName, last);
   person.lastName[MAXLAST] = 0;
   strcpy(person.state, state);
   person.state[MAXSTATE] = 0;
   person.age = age;

   return person;
}

int comparePeople(const void *personA, const void *personB) {
   Person *a, *b;
   int state, fName, lName;

   a = (Person *) personA;
   b = (Person *) personB;

   state = strcmp(a->state, b->state);
   if (state < 0)
      return -1;
   else if (state > 0)
      return 1;
   
   if (a->age < b->age)
      return -1;
   else if (a->age > b->age)
      return 1;

   lName = strcmp(a->lastName, b->lastName);
   if (lName < 0)
      return -1;
   else if (lName > 0)
      return 1;

   fName = strcmp(a->firstName, b->firstName);
   if (fName < 0)
      return -1;
   else if (fName > 0)
      return 1;

   return 0;
}

void sortPeople(const char *inFile, const char *outFile) {
   FILE *input, *output; 
   char first[MAXFIRST], last[MAXLAST], state[MAXSTATE], str[100];
   unsigned short age;
   int numPeople = 0, i = 0;
   Person person, *list;
 
   input = checkFile(inFile);

   while (fgets(str, 100, input) != NULL) 
      numPeople++;
 
   list = (Person *) malloc(sizeof(Person) * numPeople);
   rewind(input);
   
   for (i = 0; i < numPeople; i++) {
      fscanf(input, "%s %s %s %hu\n", first, last, state, &age);
      person = newPerson(first, last, state, age);
      list[i] = person;
   }
   
   fclose(input);
   qsort(list, numPeople, sizeof(Person), comparePeople);
   output = fopen(outFile, "w");

   for (i = 0; i < numPeople; i++) {
      person = list[i];
      fprintf(output, "%s %hu %s %s\n", person.state, person.age, 
         person.lastName, person.firstName);
   }
   free(list);
   fclose(output);
}
