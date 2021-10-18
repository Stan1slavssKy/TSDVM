#==========================================================================================
#
# Makefile for stack c++ project
#		author: Kurnevich Stanislav
#
#==========================================================================================

CXX       = g++
WARNINGS  = -Wall -Wextra 

DEBUG_MODE   = -g3 -O0 
RELEASE_MODE = -g0 -O3

VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all

STACK_DIR = ./stack

SOURCE = $(STACK_DIR)/main.cpp
OBJECT = $(SOURCE:.cpp=.o)
OUTPUT = stack_output

default: valgrind

valgrind: $(OUTPUT)
	valgrind $(VALGRIND_FLAGS) ./$(OUTPUT)

launch: $(OUTPUT)
	./$(OUTPUT)

$(OUTPUT): $(OBJECT)
	$(CXX) $(WARNINGS) $(DEBUG_MODE) $^ -o $(OUTPUT)

main.o: $(STACK_DIR)/main.cpp
	$(CXX) -c $^

clean:
	rm -f *.o *.a $(OBJECT) $(OUTPUT)
#==========================================================================================