intel-all:	lib/libmalloc.so	lib64/libmalloc.so

lib/libmalloc.so:	lib malloc32.o
		gcc $(CFLAGS) -g -fpic -m32 -shared -o $@ malloc32.o

lib64/libmalloc.so:	lib64 malloc64.o
		gcc $(CFLAGS) -g -fpic -shared -o $@ malloc64.o

lib:
		mkdir lib

lib64:
		mkdir lib64

malloc32.o:	malloc.c
		gcc $(CFLAGS) -g -fpic -m32 -c -o malloc32.o malloc.c

malloc64.o: malloc.c
		gcc $(CFLAGS) -g -fpic -m64 -c -o malloc64.o malloc.c

run: test.c
		gcc -Wall -g -c -o test.o test.c
		gcc -L ~/cpe453/Program1/lib64/ -lmalloc -o test test.o
		./test

clean:
		rm -f *.o *.a

