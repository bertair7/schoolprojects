#!/bin/bash

./a.out bigWords.txt > test1.out
~kmammen-grader/public/357/Project3/wf32 bigWords.txt > test1.expect
diff -q test1.out test1.expect

./a.out a.out > test5.out
~kmammen-grader/public/357/Project3/wf32 a.out > test5.expect
diff -q test5.out test5.expect

./a.out lotsOfWords1.txt > test2.out
~kmammen-grader/public/357/Project3/wf32 lotsOfWords1.txt > test2.expect
diff -q test2.out test2.expect

./a.out lotsOfWords2.txt > test3.out
~kmammen-grader/public/357/Project3/wf32 lotsOfWords2.txt > test3.expect
diff -q test3.out test3.expect

./a.out *.txt > test4.out
~kmammen-grader/public/357/Project3/wf32 *.txt > test4.expect
diff -q test4.out test4.expect

