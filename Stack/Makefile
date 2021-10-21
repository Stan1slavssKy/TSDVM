#==========================================================================================
#
# Makefile for stack c++ project
#		author: Kurnevich Stanislav
#
#==========================================================================================

CXX       = g++
WARNINGS  = -Werror -Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wenum-compare -Wfloat-equal -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo

DEBUG_MODE   = -g3 -O0 
RELEASE_MODE = -g0 -O3

VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

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