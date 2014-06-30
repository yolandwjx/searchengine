CC = gcc
OBJS = file.o html.o unit_test_file.o dictionary.o index.o hash.o interpreter.o
CFLAGS = -Wall -pedantic -std=c99 -g
EXEC = unit_test_file
SRCS = file.c unit_test_file.c file.h html.c html.h dictionary.h dictionary.c index.h index.c hash.c hash.h interpreter.h interpreter.c
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)
$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)
clean:
	rm -f *~
	rm -f *#
	rm -f *.o
	rm -f *.gch
	rm -f *.out
	rm ./unit_test_file