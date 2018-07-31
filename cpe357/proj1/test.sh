#!/bin/bash

./a.out -show < test2.txt > test2.out
~kmammen-grader/public/357/Project1/mastermind -show < test2.txt > test2.expect
diff test2.out test2.expect

./a.out -show  < test3.txt > test3.out
~kmammen-grader/public/357/Project1/mastermind -show  < test3.txt > test3.expect
diff test3.out test3.expect

./a.out -show  < test4.txt > test4.out
~kmammen-grader/public/357/Project1/mastermind -show  < test4.txt > test4.expect
diff test4.out test4.expect

./a.out -show  < test5.txt > test5.out
~kmammen-grader/public/357/Project1/mastermind -show  < test5.txt > test5.expect
diff test5.out test5.expect

./a.out -show  < test6.txt > test6.out
~kmammen-grader/public/357/Project1/mastermind -show  < test6.txt > test6.expect
diff test6.out test6.expect

./a.out -show  < test7.txt > test7.out
~kmammen-grader/public/357/Project1/mastermind -show  < test7.txt > test7.expect
diff test7.out test7.expect


