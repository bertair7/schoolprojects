import sys

def process(argv):
   validate_cmdline(argv) 
   with open_file(argv[1], 'rb') as f:
      file = process_file(f)
   return file
   
def validate_cmdline(argv):
   if len(argv) == 2:
      pass
   else:
      print 'usage: python puzzle.py <file>'
      exit(1)

def open_file(name, mode):
   try:
      return open(name, mode)
   except IOError as e:
      print >> sys.stderr, '{0}:{1}'.format(name, e.strerror)
      exit(1)

def process_file(f):
   file = f.read()
   n = file.split()
   header = n[0:4]
   pixels = process_pixels(n[4:])
   return [header, pixels]

def process_pixels(pixels):
   N = [pixels[i:i+3] for i in range(0, len(pixels), 3)]
   return N

if __name__ == '__main__':
   process(sys.argv)
