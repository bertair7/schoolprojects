import hashlib
from base64 import b64encode

def main():
   pwfile = 'passwordfile.txt'
   dictionary = 'american-english.txt'
   
   names = []
   hashes = []   

   with open(pwfile) as infile:
      for l in infile:
         n = l.split(':')
         names.append(n[0])
         
         sha = l.split('}')
         hashes.append(sha[1].strip())
      
   infile.close()
   print(names)

   with open(dictionary) as d:
      for line in d:
         h = hashlib.sha1()
         h.update(line.replace('\n',''))
         dig = b64encode(h.digest())
         
         if dig in hashes:
            i = hashes.index(dig)
            print(names[i] + ": digest = " + hashes[i] + ", pw = " + 
                  line.strip('\n'))
            
   d.close()

if __name__ == '__main__':
   main()
