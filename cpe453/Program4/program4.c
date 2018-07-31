#include "ext2.h"

FILE *fp;

FILE *openFile(char *filename, char *mode) {
   FILE *filesys = fopen(filename, mode);
   if (filesys == NULL) {
      fprintf(stderr, "File not found\n");
      exit(0);
   }
   return filesys;
}

int main(int argc, char *argv[]) {
   char *image, *dir;
   uint8_t read[512];
   char flag[3] = "-l";
   
   //alphabetically list all entries in root dir + file size
   if (argc == 2) {
      image = argv[1];
      fp = openFile(image, "r");

      /*read_data(2, 0, read, 512);
      struct ext2_super_block *s = (struct ext2_super_block*)read;
      printf("Inodes = %u\n", s->s_inodes_count); 
      printf("Blocks = %u\n", s->s_blocks_count); 
      printf("Block size = %u\n", s->s_log_block_size); 
      printf("Fragment size = %u\n", s->s_log_frag_size); 
      printf("Blocks/group = %u\n", s->s_blocks_per_group); 
      printf("Inodes/group = %u\n", s->s_inodes_per_group); 
      */

      printf("name\t\tsize\t\t\ttype\n");
      
      //block group descriptor table
      read_data(3, 0, read, 512);
      
   }
   //alphabetically list all entries from specified root dir
   else if (argc == 3) {
      image = argv[1];
      fp = openFile(image, "r");
      dir = argv[2];
   }
   //print contents of file specified
   else if (argc == 4 && strcmp(argv[1], flag) == 0) {
      image = argv[2];
      fp = openFile(image, "r");
      dir = argv[3];
   }
   else {
      fprintf(stderr, "ext2reader: invalid input \
        \nApproved options -  \
        \n\text2reader <file image> \
        \n\text2reader <file image> <directory> \
        \n\text2reader -l <file image> <file>\n");
      exit(0);
   }
   return 0;
}
