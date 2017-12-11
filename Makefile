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

OBJ_FILES = $(OBJ_DIR)/main.o \
      $(OBJ_DIR)/state.o

# Compile and link connect_four.CC to connect_four, using our compiler and
#   flags
# Depends on the main.CC file
connect_four: $(OBJ_FILES)
	$(CC) $(C_FLAGS) $(OBJ_FILES) -o connect_four

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CC) $(C_FLAGS) $(SRC_DIR)/main.cpp -c -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/state.o: $(SRC_DIR)/state.cpp
	$(CC) $(C_FLAGS) $(SRC_DIR)/state.cpp -c -o $(OBJ_DIR)/state.o

$(OBJ_DIR)/test_main.o: $(TEST_DIR)/test_main.cpp
	$(CC) $(C_FLAGS) $(TEST_DIR)/test_main.cpp -c -o $(OBJ_DIR)/test_main.o

$(TEST_DIR)/add_numbers: $(OBJ_DIR)/test_main.o $(SRC_DIR)/add_numbers.cpp $(SRC_DIR)/add_numbers.cpp $(INC_DIR)/add_numbers.h
	$(CC) $(C_FLAGS) $(OBJ_DIR)/test_main.o $(TEST_DIR)/add_numbers.cpp $(SRC_DIR)/add_numbers.cpp -o $(TEST_DIR)/add_numbers

$(TEST_DIR)/state: $(OBJ_DIR)/test_main.o $(TEST_DIR)/state.cpp $(SRC_DIR)/state.cpp $(INC_DIR)/state.h
	$(CC) $(C_FLAGS) $(OBJ_DIR)/test_main.o $(TEST_DIR)/state.cpp $(SRC_DIR)/state.cpp -o $(TEST_DIR)/state

test: $(TEST_DIR)/add_numbers $(TEST_DIR)/state
	./$(TEST_DIR)/add_numbers
	./$(TEST_DIR)/state

# Remove the executable
clean:
	rm -f connect_four test_exec
	rm -f $(OBJ_DIR)/*.o
