#!/bin/bash

~kmammen-grader/public/357/Project4/bsHost -d -g2 ~kmammen-grader/public/357/Project4/basicPlayer1 ~kmammen-grader/public/357/Project4/basicPlayer2 > test1.expect
./a.out -g2 -d ~kmammen-grader/public/357/Project4/basicPlayer1 ~kmammen-grader/public/357/Project4/basicPlayer2 > test1.out
diff test1.out test1.expect

~kmammen-grader/public/357/Project4/bsHost -d ~kmammen-grader/public/357/Project4/badPlayer ~kmammen-grader/public/357/Project4/basicPlayer2 > test2.expect
./a.out -d ~kmammen-grader/public/357/Project4/badPlayer ~kmammen-grader/public/357/Project4/basicPlayer2 > test2.out
diff test2.out test2.expect

~kmammen-grader/public/357/Project4/bsHost -d basicPlayer ~kmammen-grader/public/357/Project4/basicPlayer2 > test3.expect
./a.out -d basicPlayer ~kmammen-grader/public/357/Project4/basicPlayer2 > test3.out
diff test3.out test3.expect

