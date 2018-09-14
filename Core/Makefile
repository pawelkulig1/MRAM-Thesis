CXX= g++
FILES=  Point.o\
	    Chain.o             \
	    Plane.o             \
	    PlainDataParser.o \
	    StationaryImage.o   \
		MovingImage.o       \
		ChainSaver.o		\
		Pipe.o


FLAGS= --std=c++17
LIBS = -I/Parsers -I. -IEigen -Iboost
OUT= main.o

TEST_FLAGS= --std=c++17 -lboost_unit_test_framework


main: $(FILES) main.cpp 
	$(CXX) -o main.o main.cpp $(FILES) $(LIBS) $(FLAGS)

test: main.o tests/test2.cpp $(FILES)
	$(CXX) -o tests/test.o tests/test2.cpp $(FILES) $(TEST_FLAGS) $(LIBS)
	./tests/test.o

debug: $(FILES) main.cpp
	$(CXX) -o main.o main.cpp $(FILES) $(LIBS) $(FLAGS) -g

tdebug: main.o tests/test2.cpp
	$(CXX) -o tests/test.o tests/test2.cpp $(FILES) $(TEST_FLAGS) $(LIBS) -g
	./tests/test.o

Point.o: Point.h Point.cpp
	$(CXX) -c Point.cpp $(LIBS) $(FLAGS)

StationaryImage.o: StationaryImage.h StationaryImage.cpp 
	$(CXX) -c StationaryImage.cpp $(LIBS) $(FLAGS)

MovingImage.o: MovingImage.h MovingImage.cpp
	$(CXX) -c MovingImage.cpp $(LIBS) $(FLAGS)

Chain.o: Chain.h Chain.cpp
	$(CXX) -c Chain.cpp $(LIBS) $(FLAGS)

Plane.o: Plane.h Plane.cpp
	$(CXX) -c Plane.cpp $(LIBS) $(FLAGS)

PlainDataParser.o: Parsers/PlainDataParser.h Parsers/PlainDataParser.cpp
	$(CXX) -c Parsers/PlainDataParser.cpp $(LIBS) $(FLAGS)

ChainSaver.o: ChainSaver.h ChainSaver.cpp
	$(CXX) -c ChainSaver.cpp $(LIBS) $(FLAGS)

Pipe.o: Pipe.h Pipe.cpp
	$(CXX) -c Pipe.cpp $(LIBS) $(FLAGS)

clean:
	rm *.o
