import sys, os, base64

def main():
   if (len(sys.argv) != 3):
      print("Wrong usage of program: lab1_2.py infile outfile")
      sys.exit(0)

   i_file = sys.argv[1]
   with open(i_file, 'r') as infile:
      one = infile.read()

   rand = os.urandom(len(one))
   key = base64.b64encode(rand).decode('utf-8')

   res = ''.join(chr(ord(a) ^ ord(b)) for a,b in zip(one, key))

   o_file = sys.argv[2]
   outfile = open(o_file, 'w')
   outfile.write(res)

   res2 = ''.join(chr(ord(a) ^ ord(b)) for a,b in zip(res, key))

   print(res2)
   out2 = open("unencrypted.txt", 'w')
   out2.write(res2)
   
if __name__ == '__main__':
   main()

