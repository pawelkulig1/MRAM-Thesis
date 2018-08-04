CXX = g++
OBJ =					\
	 main.cpp   		\
	 vector.cpp 		


INCLUDES = #compilator flags here
LIBS = -I Eigen/
FLAGS = --std=c++17


all $(OBJ):
	$(CXX) $(LIBS) $(OBJ) -o GNEB $(FLAGS)

clean:
	rm -f *.o GNEB

%.o: %.cpp 
	$(CXX) -c $<

#vector.o:
#	$(CC) vector.cpp

#.cpp.o:
#	$(CC) -c $(INCLUDES) $(CFLAGS) $<
