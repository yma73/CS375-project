#ifndef GRAPH_H
#define GRAPH_H

typedef struct{
	int start;
	int weight;
	int end;
}Edges;

class DisjointSet;

class Graph{

private:
	std::vector<Edge> edges;
	int v_num;
public:
	friend class DisjointSet;
};
		 