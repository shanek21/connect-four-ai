# Useful Makefile resources:
# This powerpoint: https://web.stanford.edu/class/cs193d/handouts/make.pdf
# This introduction: http://web.stanford.edu/~aistrate/Codepedia/make.html
# This tutorial: http://mrbook.org/blog/tutorials/make/

CC = g++ # explicitly set the compiler
SRC_DIR = src
OBJ_DIR = obj
TEST_DIR = test
INC_DIR = include
LIB_DIR = lib
# -g includes extra debugging info, -Wall gives possible warnings in src code.
C_FLAGS = -g -std=c++11 -Wall

OBJS = $(OBJ_DIR)/main.o \
      $(OBJ_DIR)/state.o \
      $(OBJ_DIR)/renderer.o \
      $(OBJ_DIR)/table.o \
      $(OBJ_DIR)/solver.o


.PHONY: all directories test clean

all: directories connect_four

directories:
	mkdir -p $(OBJ_DIR)

# Compile and link connect_four.CC to connect_four, using our compiler and
#   flags
# Depends on the main.CC file
connect_four: $(OBJS)
	$(CC) $(C_FLAGS) $(OBJS) -o connect_four -lncurses

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CC) $(C_FLAGS) $(SRC_DIR)/main.cpp -c -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/state.o: $(SRC_DIR)/state.cpp
	$(CC) $(C_FLAGS) $(SRC_DIR)/state.cpp -c -o $(OBJ_DIR)/state.o

$(OBJ_DIR)/table.o: $(SRC_DIR)/table.cpp
	$(CC) $(C_FLAGS) $(SRC_DIR)/table.cpp -c -o $(OBJ_DIR)/table.o

$(OBJ_DIR)/renderer.o: $(SRC_DIR)/renderer.cpp
	$(CC) $(C_FLAGS) $(SRC_DIR)/renderer.cpp -c -o $(OBJ_DIR)/renderer.o

$(OBJ_DIR)/solver.o: $(SRC_DIR)/solver.cpp $(OBJ_DIR)/table.o
	$(CC) $(C_FLAGS) $(SRC_DIR)/solver.cpp -c -o $(OBJ_DIR)/solver.o

$(OBJ_DIR)/test_main.o: $(TEST_DIR)/test_main.cpp
	$(CC) $(C_FLAGS) $(TEST_DIR)/test_main.cpp -c -o $(OBJ_DIR)/test_main.o

$(TEST_DIR)/state: $(OBJ_DIR)/test_main.o $(TEST_DIR)/state.cpp $(OBJ_DIR)/state.o
	$(CC) $(C_FLAGS) $(OBJ_DIR)/test_main.o $(TEST_DIR)/state.cpp $(OBJ_DIR)/state.o -o $(TEST_DIR)/state

$(TEST_DIR)/solver: $(OBJ_DIR)/test_main.o $(TEST_DIR)/solver.cpp $(OBJ_DIR)/solver.o $(OBJ_DIR)/state.o $(OBJ_DIR)/table.o 
	$(CC) $(C_FLAGS) $(OBJ_DIR)/test_main.o $(TEST_DIR)/solver.cpp $(OBJ_DIR)/solver.o $(OBJ_DIR)/state.o $(OBJ_DIR)/table.o -o $(TEST_DIR)/solver

$(TEST_DIR)/table: $(OBJ_DIR)/test_main.o $(TEST_DIR)/table.cpp $(OBJ_DIR)/table.o $(OBJ_DIR)/state.o
	$(CC) $(C_FLAGS) $(OBJ_DIR)/test_main.o $(TEST_DIR)/table.cpp $(OBJ_DIR)/table.o $(OBJ_DIR)/state.o -o $(TEST_DIR)/table

test: directories $(TEST_DIR)/state $(TEST_DIR)/solver $(TEST_DIR)/table
	./$(TEST_DIR)/table
	./$(TEST_DIR)/state
	./$(TEST_DIR)/solver

# Remove the executable
clean:
	rm -f connect_four $(TEST_DIR)/state
	rm -f $(OBJ_DIR)/*.o
