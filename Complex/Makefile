CXX       = g++
WARNINGS  = -Wall -Wextra 

DEBUG_MODE   = -g3 -O0 
RELEASE_MODE = -g0 -O3

VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all

CMPL_DIR = ./complex
TEST_DIR = ./test

SOURCE = $(CMPL_DIR)/compl.cpp $(CMPL_DIR)/main.cpp $(TEST_DIR)/compl_test.cpp
OBJECT = $(SOURCE:.cpp=.o)
OUTPUT = compl_output
 
default: valgrind

valgrind: $(OUTPUT)
	valgrind $(VALGRIND_FLAGS) ./$(OUTPUT)

launch: $(OUTPUT)
	./$(OUTPUT)

$(OUTPUT): $(OBJECT)
	$(CXX) $(WARNINGS) $(DEBUG_MODE) $^ -o $(OUTPUT)

main.o: $(CMPL_DIR)/main.cpp
	$(CXX) -c $^

compl.o: $(CMPL_DIR)/compl.cpp
	$(CXX) -c $^

compl_test.o: $(TEST_DIR)/compl_test.cpp
	$(CXX) -c $^

clean:
	rm -f *.o *.a $(OBJECT) $(OUTPUT)