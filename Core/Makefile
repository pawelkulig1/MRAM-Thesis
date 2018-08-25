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

main.o: Point.o StationaryImage.o MovingImage.o Chain.o Plane.o PlainDataParser.o
	$(CXX) -o main.o main.cpp $(FILES) $(LIBS) $(FLAGS)

Point.o: Point.h Point.cpp
	$(CXX) -c Point.cpp $(LIBS) $(FLAGS)

StationaryImage.o: StationaryImage.h StationaryImage.cpp Point.h Point.cpp
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
