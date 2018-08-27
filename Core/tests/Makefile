CXX= g++
$RELATIVE=../
FILES= Point.o\
	   StationaryImage.o   \
	   MovingImage.o       \
	   Chain.o             \
	   Plane.o             \
	   PlainDataParser.o   \

FILES2 := $(addprefix ../, $(FILES))

FLAGS= --std=c++17 -lboost_unit_test_framework
LIBS= -I../Parsers/ -I../boost/ -I../Eigen/ -IParsers/


all: $(FILES2) test2.cpp
	cd .. && $(MAKE) && cd tests/
	$(CXX) -o suite1 test2.cpp $(FILES2) $(FLAGS) $(LIBS) 

