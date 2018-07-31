#include <stdlib.h>
#include <stdio.h>
#include "memmon.h"
#include "linkedList.h"

ListNode* addHead(ListNode *list, int value) {
   ListNode *head;

   head = (ListNode *) malloc(sizeof(ListNode));

   if (!head) {
      fprintf(stderr, "malloc failure attempting to add %d\n", value);
      exit(EXIT_FAILURE);
   }

   head->value = value;
   if (!list) {
      head->next = NULL;
      return head;
   }

   head->next = list;

   return head;
}

ListNode* addTail(ListNode *list, int value) {
   ListNode *tail, *temp;

   tail = (ListNode *) malloc(sizeof(ListNode));
  
   if (!tail) {
      fprintf(stderr, "malloc failure attempting to add %d\n", value);
      exit(EXIT_FAILURE);
   }

   tail->value = value;
   tail->next = NULL;

   temp = list;
   if (!temp) 
      return tail;
   
   while (temp->next) {
      temp = temp->next;
   }
   temp->next = tail;

   return list;
}

ListNode* deleteNode(ListNode *list, int index) {
   ListNode *temp, *temp2;
   int i;

   temp = list;
   for (i = 0; i < index; i++) {
      if (!temp)
         break;
      else {
         temp2 = temp;
         temp = temp->next;
      }
   }
 
   if (i != index) {
      printf("Index %d is out of bounds\n", index);
   }
   else if (index == 0) {
      temp2 = temp->next;
      free(temp);
      return temp2;
   }  
   else {
      temp2->next = temp->next;
      free(temp);
   }

   return list;
}

void printList(ListNode *list) {
   ListNode *temp;

   temp = list;

   printf("List: ");

   if (temp == NULL)
      printf("Empty\n");
   else {
      while (temp->next) {
         printf("%d ", temp->value);
         temp = temp->next;
      }
      if (temp->value)
         printf("%d\n", temp->value);
   }
}

