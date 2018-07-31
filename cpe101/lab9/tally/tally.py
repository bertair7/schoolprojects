import sys

def add_values_in_col(argv):
   validate_cmdline(argv)
   col_index = get_column(argv) - 1 
   sum = 0
   with open_file(argv[1], 'rb') as f:
      sum = process_file(f, col_index)
   print sum

def validate_cmdline(argv):
   if len(argv) == 3:
      pass
   else:
      print 'usage: python tally.py <filename> <column #>'
      exit(1)

def get_column(argv):
   try:
      return int(argv[2])
   except:
      print 'column # not valid'
      return 1

def open_file(name, mode):
   try:
      return open(name, mode)
   except IOError as e:
      print >> sys.stderr, '{0}:{1}'.format(name, e.strerror)
      exit(1)

def process_file(file, col_index):
   total = 0
   i = 1
   for line in file:
      f = line.split()
      if len(f) - 1 < col_index:
         print 'Line', i, '- out of range'
         total += 0
      else:
         total += add_number(f, col_index, i)
      i += 1
   return total

def add_number(list, index, i):
   try:
      return float(list[index])
   except:
      print 'Line:', i, '- not a number'
      return 0
      
if __name__ == '__main__':
   add_values_in_col(sys.argv) 
