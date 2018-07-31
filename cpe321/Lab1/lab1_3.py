import sys, os

def main():
   if (len(sys.argv) != 3):
      print("Wrong usage of program: lab1.py infile outfile")
      sys.exit(0)

   i_file = sys.argv[1]
   infile = open(i_file, 'r')
   with open(i_file, 'r') as infile:
      header = infile.read(54)
      one = infile.read()

   rand = os.urandom(len(one))
   #key = base64.b64encode(rand).decode('utf-8')

   res = ''.join(chr(ord(a) ^ ord(b)) for a,b in zip(one, rand))

   o_file = sys.argv[2]
   outfile = open(o_file, 'w')
   outfile.write(header)
   outfile.write(res)
   
if __name__ == '__main__':
   main()

