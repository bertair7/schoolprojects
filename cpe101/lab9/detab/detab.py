import sys

OUTFILE_NAME = "detabbed"
TAB_STOP_SIZE = 8
NUM_ARGS = 2
FILE_ARG_IDX = 1


def main(argv):
   validate_cmdline(argv)
   with open_file(argv[FILE_ARG_IDX], "r") as f:
      with open_file(OUTFILE_NAME, "w") as e:
         read_the_file(f, e)

def validate_cmdline(argv):
   if len(argv) < NUM_ARGS:
      print >> sys.stderr, "file name missing"
      sys.exit(1)

def open_file(name, mode):
   try:
      return open(name, mode)
   except IOError as e:
      print 'IO', e
      sys.exit(1)

def read_the_file(infile, outfile):
   char = 0
   c = infile.read(1)
   while (c):   
      if (c == '\t'):
         char += create_space(outfile, char)
      elif (c == '\n'):
         outfile.write('\n')
         char = 0
      else:
         outfile.write(c)
         char += 1
      c = infile.read(1)

def create_space(file, char):
   num_spaces =  TAB_STOP_SIZE - (char % TAB_STOP_SIZE)
   for i in range(num_spaces):
      file.write(' ')
   return num_spaces

if __name__ == "__main__":
   main(sys.argv)
