import sys, os, base64

def main():
   if (len(sys.argv) != 4):
      print("Wrong usage of program: lab1.py infile1 infile2 outfile")
      sys.exit(0)

   i_file1 = sys.argv[1]
   with open(i_file1, 'r') as infile:
      header = infile.read(54)
      one = infile.read()

   key = os.urandom(len(one))
   res = ''.join(chr(ord(a) ^ ord(b)) for a,b in zip(one, key))

   i_file2 = sys.argv[2]
   with open(i_file2, 'r') as infile2:
      header2 = infile2.read(54)
      two = infile2.read()

   res2 = ''.join(chr(ord(a) ^ ord(b)) for a,b in zip(two, key))

   res3 = ''.join(chr(ord(a) ^ ord(b)) for a,b in zip(one, two))

   o_file = sys.argv[3]
   outfile = open(o_file, 'w')
   outfile.write(header)
   outfile.write(res3)
   
if __name__ == '__main__':
   main()

