#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char **argv) {
   DIR *dp;
   struct dirent *dirp;
   struct stat *file;
   ino_t inode;
   dev_t device;
   char path[4097];

   memset(path, 0, sizeof(path));

   if (argc != 1) {
      fprintf(stderr, "Usage: pwd\n");
      exit(EXIT_FAILURE);
   }

   if ((dp = opendir(".")) == NULL) {
      perror("Can't open dir\n");
      exit(EXIT_FAILURE);
   }

   while ((dirp = readdir(dp)) != NULL) {
      stat(dirp->d_name, file);
      inode = file->st_ino;
      device = file->st_dev;
      strcpy(path, "/");
      strcat(path, dirp->d_name);
   }

   closedir(dp);
  
   return EXIT_SUCCESS;
}
