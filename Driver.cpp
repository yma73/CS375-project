#include "Graph.h"

using namespace std;

int main(int argc, char ** argv){
	if(argc != 2){
		perror("Please invoke as: ./Driver filename");
		exit(1);
	}
	Graph graph = Graph(argv[1]);
	graph.print();
	graph.PrimMST();
	graph.showResult();
}