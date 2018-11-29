R = GraphProducer
D = Driver
G = Graph
K = Kruskal
P = Prim
CFLAGS = -Wall -Wextra -DDEBUG -g -pedantic -std=c++14

all: $(D)

produce: $(R)

run: all
	./$(D) datasets/100vertices/1.txt
checkmem: all
	valgrind ./$(D) slide_example.txt
clean: 
	rm -rf *.o
	rm -rf output/*.txt
	rm -rf $(D)
	rm -rf $(R)

$(D): $(D).o $(P).o PriorityQueue.o $(K).o DisjointSet.o DisjointSet2.o
	g++ $(CFLAGS) $(D).o $(P).o PriorityQueue.o $(K).o DisjointSet.o DisjointSet2.o -o $(D)
$(P).o: $(P).cpp $(G).h
	g++ $(CFLAGS) -c $(P).cpp -o $(P).o
$(D).o: $(D).cpp $(G).h
	g++ $(CFLAGS) -c $(D).cpp -o $(D).o
$(R): $(R).cpp
	g++ $(CFLAGS) $(R).cpp -o $(R)
PriorityQueue.o: PriorityQueue.cpp $(G).h
	g++ $(CFLAGS) -c PriorityQueue.cpp -o PriorityQueue.o 
DisjointSet.o: DisjointSet.cpp DisjointSet.h
	g++ $(CFLAGS) -c DisjointSet.cpp -o DisjointSet.o
DisjointSet2.o: DisjointSet2.cpp DisjointSet2.h
	g++ $(CFLAGS) -c DisjointSet2.cpp -o DisjointSet2.o
$(K).o: $(K).cpp $(G).h DisjointSet.h DisjointSet2.h
	g++ $(CFLAGS) -c $(K).cpp -o $(K).o
