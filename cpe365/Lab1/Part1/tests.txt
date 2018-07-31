#!/bin/bash
## CSC 365, Fall 2017
## Garrett Leone, Ryan Blair
## Lab 1-1 test suite

## TC-0
## Test Requirement R1, R2
echo Test1==========================================
## TC-1 
## Tests Requirements R3, R4, R13
## Student cmd, existing student, then quit
## expected output: HAVIR BOBBIE 2 108 HAMER GAVIN
python schoolsearch.py << Commands
S: HAVIR
Q
Commands

echo Test2==========================================
## TC-2 
## Test Requirements R3, R4, R13
## Student cmd, student not in roster, then quit
## expected output: <blank>
python schoolsearch.py << Test2
S: BLAIR
Q
Test2

echo Test3==========================================
## TC-3 
## Test Requirements R3, R5, R6, R13
## Student cmd w/ bus, Teacher cmd, teacher exists, then quit
## expected output: HAVIR BOBBIE 0
##                  SAELEE DANILO
##                  GARTH JOHN
python schoolsearch.py << Test3
S: HAVIR B
T: FALKER
Q
Test3

echo Test4==========================================
## TC-4 
## Test Requirements R3, R7, R8, R13
## Grade cmd + exists, Bus cmd, route exists, then quit
## expected output: SAELEE DANILO
##                  GARTH JOHN
##                  PHUONG SCHOENECKER 6 109
##                  MATHILDA FINCHMAN 6 111
##                  HYE BRODERSEN 3 110
##                  BOBBIE HAVIR 2 108
##                  ELDON MASSART 4 105
##                  JOHN GARTH 1 103
##                  RANDOLPH CREMEANS 6 109
##                  CARRIE KREESE 2.85 109
python schoolsearch.py << Test4
G: 1
Bus: 0
Q
Test4

echo Test5==========================================
## TC-5 
## Test Requirements R3, R9, R13
## Grade cmd, grade exists, then quit
## expected output: SHARRI SWEDLUND 3.24 ROCIO FAFARD 55
##                  MANIE CIGANEK 2.79 ROCIO FAFARD 53
python schoolsearch.py << Test5
G: 3 H
G: 3 L
Q
Test5

echo Test6==========================================
## TC-6 
## Test Requirements R3, R10, R13
## Average Grade 4 cmd, Info cmd, then quit
## expected output: Grade: 4 Average GPA: 2.951
##                  0: 0
##                  1: 2
##                  2: 13
##                  3: 9
##                  4: 15
##                  5: 0
##                  6: 21
python schoolsearch.py << Test6
A: 4
I
Q
Test6

echo Test7==========================================
## TC-7 
## Test Requirements R3, R9, R13
## Invalid student, bus and grade cmd's; then quit
## expected output: Back to prompt
##                  Back to prompt
##                  Back to prompt
python schoolsearch.py << Test7
Stude 
Buses
G
Q
Test7


