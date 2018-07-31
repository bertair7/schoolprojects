# Ryan Blair
# TR Section
import sys

def main():
   if (len(sys.argv) != 3):
      print 'Invalid run; expected convert.py inputFile outputFile'
      sys.exit()
   else:
      filename = sys.argv[1]
      outputname = sys.argv[2]

   with open(filename, 'r') as f:
      output = open(outputname, 'w')

      csvfile = f.readlines()
      title, ext = filename.split('.')

      line = csvfile[0]
      lines = csvfile[1:len(csvfile)]

      for l in lines:
         output.write('INSERT INTO ' + title + '(' + line + ')\n')
         output.write('VALUES (' + l + ');\n\n')

      output.close()
      

if __name__ == '__main__':
   main()
