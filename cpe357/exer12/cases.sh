#!/bin/bash

./a.out < test1.in > test1.out
~kmammen-grader/public/357/Exercise12/getWord < test1.in > test1.expect
diff -q test1.out test1.expect

./a.out < test2.in > test2.out
~kmammen-grader/public/357/Exercise12/getWord < test2.in > test2.expect
diff -q test2.out test2.expect

./a.out < a.out > testa.out
~kmammen-grader/public/357/Exercise12/getWord < a.out > testa.expect
diff -q testa.out testa.expect
