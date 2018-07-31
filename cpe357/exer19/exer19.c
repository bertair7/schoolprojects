#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "memmon.h"

int main(int argc, char **argv) {
   int buffsize, fileread, filewrite, in, out;  
   char *buff;

   if (argc != 4) {
      fprintf(stderr, "Usage: cpBuffered bufsize fromfile tofile\n");
      exit(EXIT_FAILURE);
   }

   buffsize = atoi(argv[1]);
   buff = (char *) malloc(sizeof(char) * buffsize);

   if ((in = open(argv[2], O_RDONLY)) == -1) {
      perror("open");
   }
   if ((out = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
      perror("open");
   }

   while ((fileread = read(in, buff, buffsize)) > 0) {
      filewrite = write(out, buff, fileread);
      if (filewrite != fileread)
         perror("write");
   }

   free(buff);
   close(in);
   close(out);
 
   printf("Number of Allocations: %d\n", memAllocs());
   printf("   Current Allocation: %d\n", memCurrent());
   printf("      Peak Allocation: %d\n", memPeak());
 
   return EXIT_SUCCESS;
}
