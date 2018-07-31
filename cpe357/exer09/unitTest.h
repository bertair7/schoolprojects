#include <stdio.h>
#include <string.h>
#ifndef UNITTEST_H
   #define UNITTEST_H

   #define TEST_BOOLEAN(_ACTUAL,_EXPECT)\
   {\
      long _actual = _ACTUAL, _expect = _EXPECT;\
      if ((_actual && !_expect) || (!_actual && _expect) ) {\
         fprintf(stderr, "Failed test in %s at line %d:\n", __FILE__, \
            __LINE__);\
         fprintf(stderr, "   Found substitution %s, value %s, expected %s\n",\
            #_ACTUAL, _actual ? "true" : "false" , _expect ? "true" : "false");\
      }\
   }\

   #define TEST_CHAR(_ACTUAL,_EXPECT)\
   {\
      char _actual = _ACTUAL, _expect = _EXPECT;\
      if (_actual != _expect) {\
         fprintf(stderr, "Failed test in %s at line %d:\n", __FILE__, \
            __LINE__);\
         fprintf(stderr, "   Found substitution '%s', value '%c',", \
            #_ACTUAL, _actual);\
         fprintf(stderr, " expected '%c'\n", _expect);\
      }\
   }\

   #define TEST_UNSIGNED(_ACTUAL,_EXPECT)\
   {\
      unsigned long _actual = _ACTUAL, _expect = _EXPECT;\
      if (_actual != _expect) {\
         fprintf(stderr, "Failed test in %s at line %d:\n", __FILE__, \
            __LINE__);\
         fprintf(stderr, "   Found substitution %s, value %lu, expected %lu\n",\
            #_ACTUAL, _actual, _expect);\
      }\
   }\

   #define TEST_REAL(_ACTUAL,_EXPECT,_EPSILON)\
   {\
      double _actual = _ACTUAL, _expect = _EXPECT, _epsilon = _EPSILON;\
      if ((_actual > _expect + _epsilon) || (_actual < _expect - _epsilon)) {\
         fprintf(stderr, "Failed test in %s at line %d:\n", __FILE__, \
            __LINE__);\
         fprintf(stderr, "   Found substitution %s, value %g,", \
            #_ACTUAL, _actual);\
         fprintf(stderr, " expected %g +/-%g\n", _expect, _epsilon);\
      }\
   }\

   #define TEST_STRING(_ACTUAL,_EXPECT)\
   {\
      const char *_actual = _ACTUAL, *_expect = _EXPECT;\
      if (strcmp(_actual, _expect) != 0) {\
         fprintf(stderr, "Failed test in %s at line %d:\n", __FILE__, \
            __LINE__);\
         fprintf(stderr, "   Found substitution %s, value %s, expected %s\n",\
            #_ACTUAL, _actual, _expect);\
      }\
   }\

   #define TEST_SIGNED(_ACTUAL,_EXPECT)\
   {\
      long _actual = _ACTUAL, _expect = _EXPECT;\
      if (_actual != _expect) {\
         fprintf(stderr, "Failed test in %s at line %d:\n", __FILE__, \
            __LINE__);\
         fprintf(stderr, "   Found substitution %s, value %ld, expected %ld\n",\
            #_ACTUAL, _actual, _expect);\
      }\
   }\

#endif
