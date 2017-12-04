# Useful Makefile resources:
# This powerpoint: https://web.stanford.edu/class/cs193d/handouts/make.pdf
# This introduction: http://web.stanford.edu/~aistrate/Codepedia/make.html
# This tutorial: http://mrbook.org/blog/tutorials/make/

cpp = g++ # explicitly set the compiler
SRC_DIR = src
OBJ_DIR = obj
TEST_DIR = test
INC_DIR = include
LIB_DIR = lib
# -g includes extra debugging info, -Wall gives possible warnings in src code.
C_FLAGS = -g -std=c++11 -Wall

OBJ_FILES = $(OBJ_DIR)/main.o \
      $(OBJ_DIR)/state.o

# Compile and link connect_four.cpp to connect_four, using our compiler and
#   flags
# Depends on the main.cpp file
connect_four: $(OBJ_FILES)
	$(cpp) $(C_FLAGS) $(OBJ_FILES) -o connect_four

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(cpp) $(C_FLAGS) $(SRC_DIR)/main.cpp -c -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/state.o: $(SRC_DIR)/state.cpp
	$(cpp) $(C_FLAGS) $(SRC_DIR)/state.cpp -c -o $(OBJ_DIR)/state.o

$(OBJ_DIR)/test_main.o: $(TEST_DIR)/test_main.cpp
	$(cpp) $(C_FLAGS) $(TEST_DIR)/test_main.cpp -c -o $(OBJ_DIR)/test_main.o

$(TEST_DIR)/add_numbers: $(OBJ_DIR)/test_main.o $(SRC_DIR)/add_numbers.cpp $(SRC_DIR)/add_numbers.cpp $(INC_DIR)/add_numbers.h
	$(cpp) $(C_FLAGS) $(OBJ_DIR)/test_main.o $(TEST_DIR)/add_numbers.cpp $(SRC_DIR)/add_numbers.cpp -o $(TEST_DIR)/add_numbers

$(TEST_DIR)/state: $(OBJ_DIR)/test_main.o $(TEST_DIR)/state.cpp $(SRC_DIR)/state.cpp $(INC_DIR)/state.h
	$(cpp) $(C_FLAGS) $(OBJ_DIR)/test_main.o $(TEST_DIR)/state.cpp $(SRC_DIR)/state.cpp -o $(TEST_DIR)/state

test: $(TEST_DIR)/add_numbers $(TEST_DIR)/state
	./$(TEST_DIR)/add_numbers
	./$(TEST_DIR)/state

# Remove the executable
clean:
	rm -f connect_four test_exec
	rm -f $(OBJ_DIR)/*.o
