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
	./$(D) graph.txt
checkmem: all
	valgrind ./$(D) graph.txt
clean: 
	rm -rf *.o
	rm $(D)
	rm $(R)

$(D): $(D).o $(P).o
	g++ $(CFLAGS) $(D).o $(P).o -o $(D)
$(P).o: $(P).cpp $(G).h
	g++ $(CFLAGS) -c $(P).cpp -o $(P).o
$(D).o: $(D).cpp $(G).h
	g++ $(CFLAGS) -c $(D).cpp -o $(D).o
$(R): $(R).cpp
	g++ $(CFLAGS) $(R).cpp -o $(R)