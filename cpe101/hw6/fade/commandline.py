import sys

def process(argv):
   validate_cmdline(argv) 
   picture = []
   with open_file(argv[1], 'rb') as f:
      picture = process_file(f)
   flags = command_flags(argv)
   return [picture, flags]
   
def validate_cmdline(argv):
   if len(argv) == 5:
      pass
   else:
      print 'usage: python puzzle.py <file> <row-int> <col-int> <radius-int>'
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

def command_flags(argv):
   return [try_row(argv[2]), try_col(argv[3]), try_rad(argv[4])]

def try_row(str):
   try:
      return int(str)
   except:
      print 'Invalid entry for row - non-integer'
      exit(1)

def try_col(str):
   try:
      return int(str)
   except:
      print 'Invalid entry for col - non-integer'
      exit(1)

def try_rad(str):
   try:
      return int(str)
   except:
      print 'Invalid entry for radius - non-integer'
      exit(1)

if __name__ == '__main__':
   process(sys.argv)
