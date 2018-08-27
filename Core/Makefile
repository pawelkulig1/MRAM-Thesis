CXX= g++
FILES= Point.o\
	   StationaryImage.o   \
	   MovingImage.o       \
	   Chain.o             \
	   Plane.o             \
	   PlainDataParser.o \

FLAGS= --std=c++17
LIBS = -I/Parsers -I. -IEigen -Iboost
OUT= main.o

TEST_FLAGS= --std=c++17 -lboost_unit_test_framework -g


main.o: Point.o StationaryImage.o MovingImage.o Chain.o Plane.o PlainDataParser.o main.cpp
	$(CXX) -o main.o main.cpp $(FILES) $(LIBS) $(FLAGS)

test: main.o tests/test2.cpp
	$(CXX) -o tests/test.o tests/test2.cpp $(FILES) $(TEST_FLAGS) $(LIBS)
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




#run:
#	$(CXX) $(FILES) $(LIBS) -o $(OUT) $(FLAGS)
#	./$(OUT)

#all:
#	$(CXX) $(FILES) $(LIBS) -o $(OUT) $(FLAGS)

clean:
	rm *.o
