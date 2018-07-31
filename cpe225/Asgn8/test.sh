#!/bin/sh

TEST_DIR=/home/phatalsk/www/225/Assignments/Asgn8/test
EXEC_NAME=a.out

    cp -f $TEST_DIR/BigJim.txt .

    echo Evaluating test case t1: BigJim.txt the
    cp -f $TEST_DIR/t1.out .
    ./$EXEC_NAME BigJim.txt the > my_t1.out
    diff -b t1.out my_t1.out
    echo ------------------------------------------

    echo Evaluating test case t2: BigJim.txt Jim
    cp -f $TEST_DIR/t2.out .
    ./$EXEC_NAME BigJim.txt Jim > my_t2.out
    diff -b t2.out my_t2.out
    echo ------------------------------------------

    echo Evaluating test case t3: too few args
    cp -f $TEST_DIR/t3.out .
    ./$EXEC_NAME > my_t3.out
    diff -b t3.out my_t3.out
    echo ------------------------------------------

    echo Evaluating test case t4: too many args
    cp -f $TEST_DIR/t4.out .
    ./$EXEC_NAME BigJim.txt the hi > my_t4.out
    diff -b t4.out my_t4.out
    echo ------------------------------------------

	echo Evaluating test case t5: Nonexistent File
	cp -f $TEST_DIR/t5.out .
	./$EXEC_NAME BadFile blah > my_t5.out
    diff -b t5.out my_t5.out
    echo ------------------------------------------

    echo Evaluating test case t6: Dictionary
    cp -f $TEST_DIR/t6.out .
    ./$EXEC_NAME /usr/share/dict/words the > my_t6.out
    diff -b t6.out my_t6.out
    echo ------------------------------------------

    echo Evaluating test case t7: Long "the" File, no words found
    cp -f $TEST_DIR/t7.out .
    ./$EXEC_NAME $TEST_DIR/the.txt notFoundWord > my_t7.out
    diff -b t7.out my_t7.out
    echo ------------------------------------------
    
    echo Evaluating test case t8: Long "the" File, many found
    ./$EXEC_NAME $TEST_DIR/the.txt the > my_t8.out
	head -n 1000 my_t8.out > my_t8_h1000.out
	tail -n 1000 my_t8.out > my_t8_t1000.out
   wc -w < my_t8.out > my_t8_wc.out
    diff -b  $TEST_DIR/t8_h1000.out my_t8_h1000.out
    diff -b  $TEST_DIR/t8_t1000.out my_t8_t1000.out
    diff -b  $TEST_DIR/t8_wc.out my_t8_wc.out
    rm my_t8.out
    echo ------------------------------------------

