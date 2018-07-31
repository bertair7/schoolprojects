import sys
import math

filename = 'students.txt'

def main():
  options()
  data = createTable()
  chooseOptions(data) 

def chooseOptions(data):  
  option = raw_input('')
  while(option != 'Q' and option != 'Quit'):
    optArr = option.split(" ")
    length = len(optArr)

    if(length == 1):
      if(optArr[0] == 'I' or optArr[0] == 'Info'):
        info(data)
      else:
        print "Back to prompt"
        options()

    elif(length == 2):
      if(optArr[0] == 'S:' or optArr[0] == 'Student:'):
        student(data, optArr[1], False)
      elif(optArr[0] == 'T:' or optArr[0] == 'Teacher:'):
        teacher(data, optArr[1])
      elif(optArr[0] == 'B:' or optArr[0] == 'Bus:'):
        bus(data, optArr[1])
      elif(optArr[0] == 'A:' or optArr[0] == 'Average:'):
        average(data, optArr[1])
      else:
        print "Back to prompt"
        options()

    elif(length == 3):
      if((optArr[0] == 'S:' or optArr[0] == 'Student:')
        and (optArr[2] == 'B' or optArr[2] == 'Bus')):
        student(data, optArr[1], True)
      elif((optArr[0] == 'G:' or optArr[0] == 'Grade:')
        and (optArr[2] == 'L' or optArr[2] == 'Low')):
        grade(data, optArr[1], True)
      elif((optArr[0] == 'G:' or optArr[0] == 'Grade:')
        and (optArr[2] == 'H' or optArr[2] == 'High')):
        grade(data, optArr[1], False)
      else:
        print "Back to prompt"
        options()

    else:
      print "Back to prompt"
      options()

    option = raw_input('')

def grade(data, number, val):
  low = None
  high = None
  for i in data:
    if i[2] == number:
      if(low == None or high == None):
        low = i
        high = i

      if(low[5] > i[5]):
        low = i

      if(high[5] < i[5]):
        high = i

  if(val):
    print low[1] + " " + low[0] + " " + low[5] + " " + low[7] + " " + low[6] + " " + low[4]
  else:
    print high[1] + " " + high[0] + " " + high [5] + " " + high[7] + " " + high[6] + " " + high[4]



def average(data, number):
  totalNums = 0
  total = 0
  for i in data:
    if i[2] == number:
      totalNums += 1
      total += float(i[5])
  if(totalNums > 0):
    print "Grade: " + str(number) + " Average GPA: " + str('%.3f'%(total/totalNums))

def bus(data, number):
  for i in data:
    if number == i[4]:
      print i[1] + " " + i[0] + " " + i[2] + " " + i[3]


def teacher(data, lastname):
  for i in data:
    if lastname in i:
      print i[0] + " " + i[1]

def student(data, lastname, bus):
  if(bus == False):
    for i in data:
      if lastname in i:
        print i[0] + " " + i[1] + " " + i[2] + " " + i[3] + " " + i[6] + " " + i[7]
  else:
    for i in data:
      if lastname in i:
        print i[0] + " " + i[1] + " " + i[4]


def createTable():
   try:
      openFile = open(filename, 'r')
   except IOError:
      print 'cannot open'
      sys.exit()

   with openFile as f:
    content = f.readlines()
 
   data = [None] * len(content) 
   for i in range(len(content)):
      val = content[i]
      arr = [x.strip() for x in val.split(',')]
      if (len(arr) != 8):
         print "Invalid data format"
         sys.exit()
      data[i] = arr

   return data

def info(data):
  arr = [0] * 7
  for i in data:
    arr[int(i[2])] += 1

  for i in range(7):
    print str(i) + ": " + str(arr[i])



def options():
  print ("""S[tudent]: <lastname> [B[us]]\n
T[eacher]: <lastname>\n
B[us]: <number>\n
G[rade]: <number> [[H[igh]]|[L[ow]]]\n
A[verage]: <number>\n
I[nfo]\n
Q[uit]\n""")

if __name__ == "__main__":
  main()

