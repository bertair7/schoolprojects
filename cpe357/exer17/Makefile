CC       = gcc
CCFLAGS  = -std=c89 -pedantic -Wall -Werror
LDFLAGS  = -lm

all: a.out child

a.out: parent.o 
	$(CC) $(CCFLAGS) $(LDFLAGS) parent.o 

child: child.o 
	$(CC) $(CCFLAGS) -o child $(LDFLAGS) child.o 

parent.o: parent.c
	$(CC) $(CCFLAGS) -g -c $(LDFLAGS) parent.c 

child.o: child.c
	$(CC) $(CCFLAGS) -g -c $(LDFLAGS) child.c 

clean:
	rm -f a.out child parent.o child.o
