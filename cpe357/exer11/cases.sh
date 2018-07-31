#!/bin/bash

./a.out 0 < test1.in > test1.out 1>test1.out 2>test1.err
~kmammen-grader/public/357/Exercise11/linkedList64 0 < test1.in > test1.expect 1>test1.expect 2>test1E.err
diff test1.out test1.expect
diff test1.err test1E.err

./a.out 0 < test2.in > test2.out 1>test2.out 2>test2.err
~kmammen-grader/public/357/Exercise11/linkedList64 0 < test2.in > test2.expect 1>test2.expect 2>test2E.err
diff test2.out test2.expect
diff test2.err test2E.err

