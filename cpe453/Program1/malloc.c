#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define true 1
#define false 0
#define DEBUG_MALLOC 0
#define ALIGN (size_t)16
#define HEADER_SIZE 32

typedef struct {
   int free;               // check if free'd ptr
   size_t mem;             // amount of memory allocated
   void *addr;             // pointer to memory  
   struct Header *next;    // next Header
} Header;

Header *head = NULL;

void firstCall() {
   head = (Header *)sbrk(HEADER_SIZE);
   head->next = NULL;
}

// align memory to be divisible by ALIGN   
size_t alignedMem(size_t size) {
   size_t diff, total;

   if (size % ALIGN != 0) {
      diff = ALIGN - (size % ALIGN);
      total = size + diff;
   }
   else
      total = size;
   assert((total % ALIGN) == 0);
   
   return total;  
}

void *malloc(size_t size) {
   Header *new, *cur, *prev;
   size_t total;
   char buffer[60];
   void *ptr;

   // init head for first iteration
   if (head == NULL) {
      firstCall();
   }
   
   total = alignedMem(size);

   cur = head->next;
   prev = head;
   // check if first malloc call
   if (cur != NULL) {
      // check for any allocated memory blocks that already have enough memory
      // and are free
      while (cur->next != NULL) {
         // found free block with enough memory
         if (cur->free == true && total <= cur->mem) {
            cur->mem = total;
            cur->free = false;
            return cur->addr;
         }
         else {
            prev = cur;
            cur = cur->next;
         }
      }
   }

   new = (Header *)sbrk(HEADER_SIZE);
   // check for sbrk failure
   if (new == -1) 
      return NULL;

   new->free = false;
   new->next = NULL;
   new->mem = total;

   // cur is the last Header in the heap unless there is no Headers in the heap,
   // in which case prev is the head and new is the first Header in the heap
   if (cur == NULL)
      prev->next = new;
   else
      cur->next = new;
  
   ptr = sbrk(total);
   // check for sbrk failure
   if (ptr == -1) 
      return NULL;
   else if (size == 0)
      new->addr = NULL;
   else 
      new->addr = ptr;
 
#if DEBUG_MALLOC  
   snprintf(buffer, 60, "MALLOC: malloc(%d)        => (ptr=%p, size=%d)",
      size, ptr, total);
   puts(buffer);
#endif

   return new->addr;
}

void free(void *ptr) {
   Header *cur, *prev, *ahead;
   size_t diff;
   char buffer[30];

   // if NULL pointer, no operation
   if (ptr == NULL) {
      return;
   }

   cur = head->next;
   prev = head;

   while (cur != NULL && cur->addr != ptr) {
      prev = cur;
      cur = cur->next;
   }

   // if cur is NULL, no Header operation
   if (cur == NULL) {

      // check for ptr w/in a memory block
      if (prev->addr < ptr) {
         diff = alignedMem(ptr - prev->addr);
         prev->mem -= diff;
      }
      return;
   }
   
   if (cur->free == false) {
      cur->free = true;

      // if previous block is also free, merge to prevent fragmentation
      if (prev->free == true) {
         prev->next = cur->next;
         prev->mem += (cur->mem + sizeof(Header));
      }

      // same check with block ahead
      ahead = cur->next;
      if (ahead != NULL && ahead->free == true) {
         prev->next = ahead->next;
         prev->mem += (ahead->mem + sizeof(Header));
      }
   }
   
#if DEBUG_MALLOC  
   snprintf(buffer, 30, "MALLOC: free(%p)", ptr);
   puts(buffer);
#endif
}

void *calloc(size_t nmemb, size_t size) {
   Header *new, *cur, *prev;
   void *ptr;
   size_t total;
   char buffer[100];

   // init head for first iteration
   if (head == NULL) {
      firstCall();
   }

   total = alignedMem(nmemb * size);
  
   cur = head->next;
   prev = head;
   // check if first malloc call
   if (cur != NULL) {
      // check for any allocated memory blocks that already have enough memory
      // and are free
      cur = head->next;
      while (cur->next != NULL) {
         // found free block with enough memory
         if (cur->free == true && total <= cur->mem) {
            cur->mem = total;
            cur->free = false;
            return cur->addr;
         }
         else {
            prev = cur;
            cur = cur->next;
         }
      }
   }

   new = (Header *)sbrk(HEADER_SIZE);
   // check for sbrk failure
   if (new == -1) 
      return NULL;

   new->free = false;
   new->next = NULL;
   new->mem = total;

   if (cur == NULL)
      prev->next = new;
   else
      cur->next = new;
   
   ptr = sbrk(total);
   // check for sbrk failure
   if (ptr == -1) 
      return NULL;
   else if (nmemb == 0 || size == 0)
      new->addr = NULL;
   else 
      new->addr = ptr;
   
#if DEBUG_MALLOC  
   snprintf(buffer, 100, "MALLOC: calloc(%d,%d)    => (ptr=%p, size=%d)",
      nmemb, size, ptr, new->mem);
   puts(buffer);
#endif

   return new->addr;
}

void *copyDataToEnd(Header *cur, size_t size) {
   Header *new, *last;
   size_t total;
   void *ptr;

   // go to end of heap
   last = cur->next;
   
   // called by realloc, which proved this Header is not the last in the heap
   assert(last != NULL);
   while (last->next != NULL) {
      last = last->next;
   }

   total = alignedMem(size);

   new = (Header *)sbrk(HEADER_SIZE);
   // check for sbrk failure
   if (new == -1) 
      return cur->addr;

   new->free = false;
   new->next = NULL;
   new->mem = total;

   last->next = new;

   ptr = sbrk(total);
   // check for sbrk failure
   if (ptr == -1) 
      return cur->addr;
   else 
      new->addr = ptr;

   // copy data from cur to new   
   memcpy(new->addr, cur->addr, cur->mem);
   free(cur->addr);

   return new->addr;
}

void *realloc(void *ptr, size_t size) {
   Header *new, *cur, *nextPtr;
   size_t diff;
   void *newBreak;
   char buffer[100];

   // if ptr is NULL, same behavior as malloc
   if (ptr == NULL) {
      return malloc(size);
   }

   // if size is 0 and ptr is not NULL, same behavior as free
   if (size == 0 && ptr != NULL) {
      free(ptr);
      return ptr;
   }

   // find ptr in heap
   cur = head->next;
   while (cur->addr != NULL && cur->addr != ptr) {
      cur = cur->next;
   }
   
   // found the pointer
   if (cur->addr == ptr) {
      diff = cur->mem - size;

      // last in the heap
      if (cur->next == NULL) {

         // realloc for less memory
         if (size <= cur->mem) {
            cur->mem = alignedMem(cur->mem - diff);
            newBreak = cur->addr + cur->mem;

            int i = brk(newBreak);
            // check for brk failure, if so, maintain original ptr and header
            if (i == -1) {
               cur->mem = alignedMem(cur->mem + diff);
               return cur->addr;
            }
         }
      
         // more memory
         else {
            cur->mem = alignedMem(cur->mem + diff);
            newBreak = cur->addr + cur->mem;
            
            int i = brk(newBreak);
            // check for brk failure, if so, maintain original ptr and header
            if (i == -1) {
               cur->mem = alignedMem(cur->mem - diff);
               return cur->addr;
            }
         }
      }
      // in the middle, after head
      else {
         
         // if enough memory already allocated, original ptr is fine
         if (cur->mem < size) {
            nextPtr = cur->next;
            size_t d = 0;
            int complete = 0;

            // check to see if next header/s is/are free + has enough space
            while (nextPtr != NULL && nextPtr->free) {
               diff -= (sizeof(Header) + nextPtr->mem);
               if (diff <= 0) {
                  cur->mem += d + sizeof(Header) + nextPtr->mem;
                  complete = 1;
                  break;
               }
               else {
                  d += sizeof(Header) + nextPtr->mem;
                  nextPtr = nextPtr->next;
               }
            }
            
            // not enough room, must copy data and make new Header at end
            // and free this Header
            if (!complete) 
               cur->addr = copyDataToEnd(cur, size);
         }
         else {
            cur->mem = size;
         }
      }
   }
   // unable to find the pointer, ptr was moved, same behavior as free
   else {
      free(ptr);
      return ptr;
   }

#if DEBUG_MALLOC  
   snprintf(buffer, 100, "MALLOC: realloc(%p,%d)   => (ptr=%p, size=%d)",
      ptr, size, cur->addr, cur->mem);
   puts(buffer);
#endif

   return cur->addr;
}

