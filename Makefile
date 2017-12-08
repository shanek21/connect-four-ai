# Useful Makefile resources:
# This powerpoint: https://web.stanford.edu/class/cs193d/handouts/make.pdf
# This introduction: http://web.stanford.edu/~aistrate/Codepedia/make.html
# This tutorial: http://mrbook.org/blog/tutorials/make/

CC = g++ # explicitly set the compiler
SRCDIR = src
TESTDIR = test
INCDIR = include
LIBDIR = lib

# -g includes extra debugging info, -Wall gives possible warnings in src code.
CFLAGS = -g -std=c++11 -Wall

all: connect_four

# Compile and link connect_four.cpp to connect_four, using our compiler and
#   flags
# Depends on the connect_four.cpp file
connect_four: $(SRCDIR)/connect_four.cpp
	$(CC) $(CFLAGS) $(SRCDIR)/connect_four.cpp -o connect_four

test_main.o: $(TESTDIR)/test_main.cpp
	$(CC) $(CFLAGS) $(TESTDIR)/test_main.cpp -c

test_exec: test_main.o $(TESTDIR)/test.cpp $(SRCDIR)/add_numbers.cpp $(INCDIR)/add_numbers.h
	$(CC) $(CFLAGS) test_main.o $(TESTDIR)/test.cpp $(SRCDIR)/add_numbers.cpp -o test_exec

test: test_exec
	./test_exec

# Remove the executable
clean:
	rm -f connect_four test_exec
	rm *.o
