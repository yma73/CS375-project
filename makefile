P = GraphProducer
CFLAGS = -Wall -Wextra -DDEBUG -g -pedantic -std=c++14

all: $(P)
	
run: all
	./$(P) 10 10
checkmem: all
	valgrind ./$(P) 10 10
	
clean: 
	rm -rf *.o
	rm $(P)
	rm graph.txt

$(P): $(P).o
	g++ $(CFLAGS) $(P).o -o $(P)
$(P).o: $(P).cpp
	g++ $(CFLAGS) -c $(P).cpp -o $(P).o
