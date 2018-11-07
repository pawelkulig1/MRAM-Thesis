CXX= g++
FILES := $(patsubst sources/%.cpp,outs/%.o,$(wildcard sources/*.cpp))
PARSERS:= $(patsubst sources/Parsers/%.cpp,outs/%.o,$(wildcard sources/Parsers/*.cpp))
ALL_FILES:= $(FILES) $(PARSERS)
FLAGS := --std=c++17 -Wall -pedantic -g
LIBS := -I/Parsers -I. -Ilibs/Eigen -Ilibs/boost
OUT= main.o

TEST_FLAGS= --std=c++17 -lboost_unit_test_framework

main: $(ALL_FILES) main.cpp
	$(CXX) -o main.o main.cpp $(ALL_FILES) $(LIBS) $(FLAGS)
	$(shell make gt)

test: testChain.o testFixedDistance.o
	$(CXX) -o tests/mainSuite.o tests/main.cpp $(FILES) $(LIBS) 
	./tests/mainSuite.o

testChain.o: tests/testChain.cpp $(FILES)
	$(CXX) -o tests/testChain.o tests/testChain.cpp $(FILES) $(TEST_FLAGS) $(LIBS) -c

testFixedDistance.o: tests/testFixedDistance.cpp $(FILES)
	$(CXX) -o tests/testFixedDistance.o tests/testFixedDistance.cpp $(FILES) $(TEST_FLAGS) $(LIBS) -c

outs/%.o: sources/%.cpp sources/%.h
	$(CXX) -c $< $(LIBS) $(FLAGS) -o $@

outs/%.o: sources/Parsers/%.cpp sources/Parsers/%.h	
	$(CXX) -c $< $(LIBS) $(FLAGS) -o $@

clean:
	rm outs/*.o
	rm tests/*.o

gt: $(FILES) main.cpp 
	find sources -name "*.cpp" -or -name "*.h" > gtagsFiles;
	find . -name "main.cpp" >> gtagsFiles;
	gtags -f gtagsFiles;
	rm gtagsFiles
