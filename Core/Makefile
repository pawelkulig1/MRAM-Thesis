CXX= g++
FILES := $(patsubst sources/%.cpp,outs/%.o,$(wildcard sources/*.cpp))
FLAGS := --std=c++17 -Wall -pedantic -g
LIBS := -I/Parsers -I. -Ilibs/Eigen -Ilibs/boost
OUT= main.o

TEST_FLAGS= --std=c++17 -lboost_unit_test_framework

main: $(FILES) main.cpp
	$(CXX) -o main.o main.cpp $(FILES) $(LIBS) $(FLAGS)
	$(shell make gt)

test: testChain.o testFixedDistance.o
	$(CXX) -o tests/mainSuite.o tests/main.cpp $(FILES) $(LIBS) 
	./tests/mainSuite.o

testChain.o: tests/testChain.cpp $(FILES)
	$(CXX) -o tests/testChain.o tests/testChain.cpp $(FILES) $(TEST_FLAGS) $(LIBS) -c

testFixedDistance.o: tests/testFixedDistance.cpp $(FILES)
	$(CXX) -o tests/testFixedDistance.o tests/testFixedDistance.cpp $(FILES) $(TEST_FLAGS) $(LIBS) -c

outs/%.o: sources/%.cpp sources/%.h;
	$(CXX) -c $< $(LIBS) $(FLAGS) -o $@ -g

clean:
	rm outs/*.o
	rm tests/*.o

gt: $(FILES) main.cpp 
	find sources -name "*.cpp" -or -name "*.h" > gtagsFiles;
	find . -name "main.cpp" >> gtagsFiles;
	gtags -f gtagsFiles;
	rm gtagsFiles
