# Useful Makefile resources:
# This powerpoint: https://web.stanford.edu/class/cs193d/handouts/make.pdf
# This introduction: http://web.stanford.edu/~aistrate/Codepedia/make.html
# This tutorial: http://mrbook.org/blog/tutorials/make/

CC := g++ # explicitly set the compiler
SRCDIR := src

# -g includes extra debugging info, -Wall gives possible warnings in src code.
CFLAGS := -g -Wall

all: connect_four

# compile and link connect_four.cpp to connect_four, using our compiler and
#   and flags
# depends on the connect_four.cpp file
connect_four: $(SRCDIR)/connect_four.cpp
	$(CC) $(CFLAGS) $(SRCDIR)/connect_four.cpp -o connect_four

# remove the executable
clean:
	rm connect_four
