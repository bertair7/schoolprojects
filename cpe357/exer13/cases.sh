#!/bin/bash

./a.out < randomPeople.txt > test.out
~kmammen-grader/public/357/Exercise12/getWord < randomPeople.txt > test.expect
diff -q test.out test.expect

