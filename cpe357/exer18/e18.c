#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

static void printDirectory(struct stat *child, DIR *cDir, ino_t inode, 
   dev_t device) {
   struct stat *parent;
   DIR *pDir;
   struct dirent *pDirent;
   ino_t pInode;
   dev_t pDevice;

   if (inode == device) {
      pDirent = readdir(cDir);
      printf("/%s", pDirent->d_name[inode]);
      closedir(cDir);
   }
   else {
      chdir("..");
      pDir = opendir(".");
      pDirent = readdir(pDir);
      stat(pDirent->d_name, );
      pDevice = parent->st_dev; 
      pInode = parent->st_ino;

      printDirectory(parent, pInode, pDevice);
      printf("/%s", pDir->d_name[inode]);
      closedir(pDir);
   }
}

int main(int argc, char **argv) {
   struct stat *file;
   DIR *dp;
   struct dirent *dirp;
   ino_t inode;
   dev_t device;

   if (argc != 1) {
      fprintf(stderr, "Usage: pwd\n");
      exit(EXIT_FAILURE);
   }

   if ((dp = opendir(".")) == NULL)
      perror("Can't open dir\n");
   dirp = readdir(dp);
   stat(dirp->d_name, file);
   device = file->st_dev;
   inode = file->st_ino;

   printDirectory(file, dirp, inode, device);
   closedir(dirp);
  
   return EXIT_SUCCESS;
}
