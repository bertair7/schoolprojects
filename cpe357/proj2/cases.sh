#!/bin/bash

./a.out a.out Makefile -l -w > testa.out
~kmammen-grader/public/357/Project2/swc a.out Makefile -l -w > testa.expect
diff testa.out testa.expect

./a.out < test1.in > test1.out
~kmammen-grader/public/357/Project2/swc < test1.in > test1.expect
diff test1.out test1.expect

./a.out -w test2.in -c > test2.out
~kmammen-grader/public/357/Project2/swc -w test2.in -c > test2.expect
diff test2.out test2.expect

./a.out test1.in test2.in -c > test12.out
~kmammen-grader/public/357/Project2/swc test1.in test2.in -c > test12.expect
diff test12.out test12.expect


