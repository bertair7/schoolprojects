#!/bin/bash

~kmammen-grader/public/357/Project6/lzwCompress64 small.in
mv small.in.lzw small.in.expect
./a.out small.in
diff -q small.in.lzw small.in.expect

#./a.out -r14 crazyWords.txt
#diff -q crazyWords.txt.lzw test3.expect

#./a.out -r11 lotsOfWords2.txt
#diff -q lotsOfWords2.txt test4.expect

~kmammen-grader/public/357/Project6/lzwCompress64 core3out
mv core3out.lzw core3expect
./a.out core3out
diff -q core3out.lzw core3expect

~kmammen-grader/public/357/Project6/lzwCompress64 core4out
mv core4out.lzw core4expect
./a.out core4out
diff -q core4out.lzw core4expect

~kmammen-grader/public/357/Project6/lzwCompress64 core5out
mv core5out.lzw core5expect
./a.out core5out
diff -q core5out.lzw core5expect

#~kmammen-grader/public/357/Project6/lzwCompress64 binout
#mv binout.lzw binexpect
#./a.out binout
#diff -q binout.lzw binexpect

~kmammen-grader/public/357/Project6/lzwCompress64 -r10 bigout
mv bigout.lzw bigexpect
./a.out -r10 bigout
diff -q bigout.lzw bigexpect

~kmammen-grader/public/357/Project6/lzwCompress64 smallout
mv smallout.lzw smallexpect
./a.out smallout
diff -q smallout.lzw smallexpect

