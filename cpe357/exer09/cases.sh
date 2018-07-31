#!/bin/bash

./a.out < test1.in > test1.out 1>test1.out 2>test1.err
~kmammen-grader/public/357/Exercise9/unitTestDriver64 < test1.in > test1.expect 1>test1.expect 2>testR1.err
diff test1.out test1.expect
diff test1.err testR1.err
