CXXFLAGS = -Wall -std=c++11

OBJECTS = randint.o board.o main.o

2048: $(OBJECTS)
	$(CXX) $(OBJECTS) -o 2048

randint.o: randint.cpp randint.h
board.o: board.cpp board.h randint.h
main.o: main.cpp board.h

clean:
	rm $(OBJECTS) 2048