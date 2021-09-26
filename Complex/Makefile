CXX       = g++
WARNINGS  = -Wall -Wextra 

DEBUG_MODE   = -g3 -O0 
RELEASE_MODE = -g0 -O3

VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all

SOURCE = compl.cpp main.cpp compl_test.cpp
OBJECT = $(SOURCE:.cpp=.o)
OUTPUT = compl_output
 
default: valgrind

valgrind: $(OUTPUT)
	valgrind $(VALGRIND_FLAGS) ./$(OUTPUT)

launch: $(OUTPUT)
	./$(OUTPUT)

$(OUTPUT): $(OBJECT)
	$(CXX) $(WARNINGS) $(DEBUG_MODE) $^ -o $(OUTPUT)

main.o: main.cpp
	$(CXX) -c $^

compl.o: compl.cpp
	$(CXX) -c $^

compl_test.o: compl_test.cpp
	$(CXX) -c $^

clean:
	rm -f *.o *.a $(OBJECT) $(OUTPUT)