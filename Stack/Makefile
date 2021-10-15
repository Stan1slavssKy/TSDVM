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

default: debug

debug: $(OUTPUT)
	valgrind $(VALGRIND_FLAGS) ./$(OUTPUT)

launch: $(OUTPUT)
	./$(OUTPUT)

$(OUTPUT): $(OBJECT)
	$(CXX) $(DEBUG_MODE) $(OBJECT) -o $@

.cpp.o: $(CXX) -c $(WARNINGS) $< -o $@

clean:
	rm -f *.o *.a $(OBJECT) $(OUTPUT)

#==========================================================================================