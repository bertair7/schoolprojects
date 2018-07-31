/*
 * Provided source for Exam 1, Problem 3 - DO NOT MODIFY !!!
 * 
 * Note that you are not required to turn in this provided file but it will
 * not be a problem if you do.
 */

#ifndef EXAM1P3_H
#define EXAM1P3_H

/*
 * Structure you are required to use
 */
typedef struct results
{
   unsigned start, length;
} Results;

/*
 * Prototype of the function you must write in a separate source file
 *
 * Note that the 'size' argument indicates how many elements are in the
 * array and are considered part of the sequence and IS NOT its actual
 * allocated memory size. That being said, 'size' is a commonly used name
 * to use in situations like this.
 */
Results findSequence(int array[], int size);

#endif
