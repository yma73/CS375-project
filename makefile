R = GraphProducer
D = Driver
G = Graph
K = Kruskal
P = Prim
CFLAGS = -Wall -Wextra -DDEBUG -g -pedantic -std=c++14

all: $(D)

produce: $(R)
	./$(R) 10 10
run: all
	./$(D) slide_example.txt
checkmem: all
	valgrind ./$(D) slide_example.txt
clean: 
	rm -rf *.o
	rm $(D)
	rm $(R)

$(D): $(D).o $(P).o PriorityQueue.o
	g++ $(CFLAGS) $(D).o $(P).o PriorityQueue.o -o $(D)
$(P).o: $(P).cpp $(G).h
	g++ $(CFLAGS) -c $(P).cpp -o $(P).o
$(D).o: $(D).cpp $(G).h
	g++ $(CFLAGS) -c $(D).cpp -o $(D).o
$(R): $(R).cpp
	g++ $(CFLAGS) $(R).cpp -o $(R)
PriorityQueue.o: PriorityQueue.cpp $(G).h
	g++ $(CFLAGS) -c PriorityQueue.cpp -o PriorityQueue.o 