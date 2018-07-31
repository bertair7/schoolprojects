#!/bin/bash

./a.out < test1.in > test1.out 1>test1.out 2>test1.err
~kmammen-grader/public/357/Exam2/823472/P2/reference < test1.in > test1.expect 1>test1.expect 2>test1E.err
diff test1.out test1.expect
diff test1.err test1E.err

./a.out < test2.in > test2.out
~kmammen-grader/public/357/Exam2/823472/P2/reference < test2.in > test2.expect
diff test2.out test2.expect

