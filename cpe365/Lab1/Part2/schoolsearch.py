## Garrett Leone
## Ryan Blair
## TR Section


import sys
import math

teachers = 'teachers.txt'
lists = 'list.txt'

def main():
  options()
  listData = createTable(lists, 6)
  teacherData = createTable(teachers, 3)
  chooseOptions(listData, teacherData) 

def chooseOptions(listData, teacherData):  
  option = raw_input('')
  while(option != 'Q' and option != 'Quit'):
    optArr = option.split(" ")
    length = len(optArr)

    if(length == 1):
      if(optArr[0] == 'I' or optArr[0] == 'Info'):
        info(listData)
      if(optArr[0] == 'E' or optArr[0] == 'Enrollment'):
        enrollment(listData)
      else:
        options()

    elif(length == 2):
      if(optArr[0] == 'S:' or optArr[0] == 'Student:'):
        student(listData, teacherData, optArr[1], False)
      elif(optArr[0] == 'T:' or optArr[0] == 'Teacher:'):
        teacher(listData, teacherData, optArr[1])
      elif(optArr[0] == 'B:' or optArr[0] == 'Bus:'):
        bus(listData, optArr[1])
      elif(optArr[0] == 'A:' or optArr[0] == 'Average:'):
        average(listData, optArr[1])
      elif(optArr[0] == 'C:' or optArr[0] == 'Classroom:'):
        classroom(listData, teacherData, optArr[1], True)
      elif(optArr[0] == 'In:' or optArr[0] == 'Instructors'):
        instructors(listData, teacherData, optArr[1])
      else:
        options()

    elif(length == 3):
      if((optArr[0] == 'S:' or optArr[0] == 'Student:')
        and (optArr[2] == 'B' or optArr[2] == 'Bus')):
        student(listData, None, optArr[1], True)
      elif((optArr[0] == 'G:' or optArr[0] == 'Grade:')
        and (optArr[2] == 'L' or optArr[2] == 'Low')):
        grade(listData, teacherData, optArr[1], True)
      elif((optArr[0] == 'G:' or optArr[0] == 'Grade:')
        and (optArr[2] == 'H' or optArr[2] == 'High')):
        grade(listData, teacherData, optArr[1], False)
      elif((optArr[0] == 'C:' or optArr[0] == 'Classroom:')
        and (optArr[2] == 'T' or optArr[2] == 'Teacher')):
        classroom(listData, teacherData, optArr[1], False)
      elif((optArr[0] == 'A:' or optArr[0] == 'Analytics:')
        and (optArr[2] == 'G' or optArr[2] == 'Grade')):
        gradeAnalytics(listData, optArr[1])
      elif((optArr[0] == 'A:' or optArr[0] == 'Analytics:')
        and (optArr[2] == 'T' or optArr[2] == 'Teacher')):
        teacherAnalytics(listData, teacherData, optArr[1])
      elif((optArr[0] == 'A:' or optArr[0] == 'Analytics:')
        and (optArr[2] == 'B' or optArr[2] == 'Bus')):
        busAnalytics(listData, optArr[1])
      else:
        options()

    else:
      options()

    option = raw_input('')

def busAnalytics(listData, bus):
  total = 0
  nums = 0
  high = -1
  low = -1
  for i in listData:
    if i[4] == bus:
      if(high == -1 or low == -1):
        high = float(i[5])
        low = float(i[5])
      total += float(i[5])
      nums += 1
      if float(i[5]) > high:
        high = float(i[5])
      if float(i[5]) < low:
        low = float(i[5])
  if nums != 0:
    print "Bus Route: " + str(bus) + "\nAverage GPA: " + str('%.2f'%(total/nums)) + " High: " + str(high) + " Low: " + str(low)

def teacherAnalytics(listData, teacherData, teacher):
  total = 0
  nums = 0
  high = -1
  low = -1
  classNum = -1
  for i in teacherData:
    if i[0] == teacher:
      classNum = i[2]
  if classNum != -1:
    for j in listData:
      if j[3] == classNum:
        if(high == -1 or low == -1):
          high = float(j[5])
          low = float(j[5])
        total += float(j[5])
        nums += 1
        if float(j[5]) > high:
          high = float(j[5])
        if float(j[5]) < low:
          low = float(j[5])
  if nums != 0:
    print "Teacher: " + teacher + "\nAverage GPA: " + str('%.2f'%(total/nums)) + " High: " + str(high) + " Low: " + str(low)

def gradeAnalytics(listData, grade):
  total = 0
  nums = 0
  high = -1
  low = -1
  for i in listData:
    if i[2] == grade:
      if(high == -1 or low == -1):
        high = float(i[5])
        low = float(i[5])
      total += float(i[5])
      nums += 1
      if float(i[5]) > high:
        high = float(i[5])
      if float(i[5]) < low:
        low = float(i[5])
  if nums != 0:
    print "Grade: " + str(grade) + "\nAverage GPA: " + str('%.2f'%(total/nums)) + " High: " + str(high) + " Low: " + str(low)

def instructors(listData, teacherData, number):
  rooms = []
  for i in listData:
    if i[2] == number and i[3] not in rooms:
      rooms.append(i[3])
  for j in teacherData:
    if j[2] in rooms:
      print j[0] + " " + j[1]

def enrollment(listData):
  status = dict()
  for i in listData:
    if i[3] in status:
      status.update({i[3]:(status[i[3]] + 1)})
    else:
      status.update({i[3]:1})
  for i in sorted(status):
    print i + ": " + str(status[i])

def classroom(listData, teacherData, number, student):
  if(student):
    for i in listData:
      if i[3] == number:
        print i[0] + " " + i[1]
  else:
    for i in teacherData:
      if i[2] == number:
        print i[0] + " " + i[1]

def grade(listData, teacherData, number, val):
  low = None
  high = None
  string = ''
  for i in listData:
    if i[2] == number:
      if(low == None or high == None):
        low = i
        high = i

      if(low[5] > i[5]):
        low = i

      if(high[5] < i[5]):
        high = i

  if(val and low):
    string = low[1] + " " + low[0] + " " + low[5]
    for j in teacherData:
      if low[3] == j[2]:
        string += " " + j[1] + " " + j[0] + " " + low[4]
        print string
  elif(high):
    string = high[1] + " " + high[0] + " " + high [5]
    for j in teacherData:
      if high[3] == j[2]:
        string += " " + j[1] + " " + j[0] + " " + high[4]
        print string

def average(listData, number):
  totalNums = 0
  total = 0
  for i in listData:
    if i[2] == number:
      totalNums += 1
      total += float(i[5])
  if(totalNums > 0):
    print "Grade: " + str(number) + " Average GPA: " + str('%.3f'%(total/totalNums))

def bus(listData, number):
  for i in listData:
    if number == i[4]:
      print i[1] + " " + i[0] + " " + i[2] + " " + i[3]

def teacher(listData, teacherData, lastname):
  for i in teacherData:
    if lastname in i:
      classNum = i[2]
      for j in listData:
        if classNum == j[3]:
          print j[0] + " " + j[1]

def student(listData, teacherData, lastname, bus):
  string = ''
  if(bus == False):
    for i in listData:
      if lastname in i:
        string = i[0] + " " + i[1] + " " + i[2] + " " + i[3]
        for j in teacherData:
          if i[3] in j:
            string += " " + j[0] + " " + j[1]
            print string
  else:
    for i in listData:
      if lastname in i:
        print i[0] + " " + i[1] + " " + i[4]

def createTable(filename, number):
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
    if(len(arr) != number):
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
C[lassroom]: <number> [T[eacher]]\n
In[structors]: <number>\n
E[nrollment]\n
A[nalytics]: <[number]|[name]> [[G[rade]]|[T[eacher]]|[B[us]]\n
I[nfo]\n
Q[uit]\n""")

if __name__ == "__main__":
  main()

