#!/bin/bash

./a.out < test1.in > test1.out
~kmammen-grader/public/357/Exercise20/bitOps < test1.in > test1.expect
diff test1.out test1.expect

./a.out < test2.in > test2.out
~kmammen-grader/public/357/Exercise20/bitOps < test2.in > test2.expect
diff test2.out test2.expect

