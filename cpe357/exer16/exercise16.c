#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXLINE 4096

int main (void) {
   char buf[MAXLINE];
   pid_t pid;
   int status;

   printf("%% ");
   while(fgets(buf, MAXLINE, stdin) != NULL) {
      if (buf[strlen(buf) - 1] == '\n')
         buf[strlen(buf) - 1] = 0;

      if ((pid = fork()) < 0) {
         perror(NULL);
      }
      else if (pid == 0) {
         execlp(buf, buf, (char *)0);
         fprintf(stderr, "couldn't execute: %s\n", buf);
         exit(EXIT_FAILURE);
      }

      if ((pid = waitpid(pid, &status, 0)) < 0)
         perror(NULL);
      printf("%% ");
   }
   exit(0);
}
