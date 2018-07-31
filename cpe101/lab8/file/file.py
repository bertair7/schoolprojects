import sys

def main(argv):
   validate_cmdline(argv)
   with open_file(argv[1], 'rb') as f:
      process_file(f)

def validate_cmdline(argv):
   if len(argv) == 2:
      pass
   else:
      print "Too few/many arguments in command line"
      exit(1)

def open_file(name, mode):
   try:
      return open(name, mode)
   except IOError as e:
      print >> sys.stderr, '{0}:{1}'.format(name, e.strerror)
      exit(1)

def process_file(f):
   for line in f:
      nums = line.split()
      if len(nums) == 2:
         p = add_numbers(nums)
         if p != None: 
            print p
      else:
         print 'Line missing a value/has too many values'

def add_numbers(nums):
   try:
      return float(nums[0]) + float(nums[1])
   except:
      print 'Cannot convert value(s) to float'

if __name__ == '__main__':
   main(sys.argv)
