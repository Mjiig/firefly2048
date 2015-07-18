CXXFLAGS = -Wall -std=c++11

OBJECTS = rand.o board.o main.o neuron.o network.o

2048: $(OBJECTS)
	$(CXX) $(OBJECTS) -o 2048

rand.o: rand.cpp rand.h
board.o: board.cpp board.h rand.h
main.o: main.cpp board.h
neuron.o: neuron.cpp neuron.h
network.o: network.cpp network.h neuron.h

clean:
	rm $(OBJECTS) 2048
