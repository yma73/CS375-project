#ifndef GRAPH_H
#define GRAPH_H

#include<cstdlib>
#include<iostream>
#include<string>
#include<cstdio>
#include<vector>
#include<sstream>
#include<string.h>
#include<fstream>
#include<climits>
#include<time.h>

#define HANDLE 0

typedef struct{
	int start;
	int weight;
	int end;
}Edge;

/*A struct Node for Prim's algorithm*/
typedef struct{
	int id;
	int key;
	int parent;
	std::vector<Edge> adj;
}Node;

class Graph{

private:
	std::vector<Edge> edges;
	int v_num;

	/*Members needed for prim's algorithm*/
	std::vector<Node*> nodes;//The adj-list representation of a graph
	std::vector<Node*> non_tree_nodes;//a min priority queue of non-tree-nodes: min-heap/array implementation
	std::vector<int> handles;

public:
	Graph(std::string filename);
	~Graph();
	std::vector<int> stringSplit(std::string s);
	void print();

	/*Functions needed for Prim's algorithm*/
	Node* findNodeHeap(int id);
	int findNodeIndex(int id);
	Node* findNodeArray(int id);
	void insertNode(int id, int w);
	void minHeapify(int i);
	bool isEmpty();
	int right(int i);
	int left(int i);
	int parent(int i);
	void heapDecreaseKey(int pos, int key);
	void arrayDecreaseKey(int pos, int key);
	Node* arrayExtractMin();
	Node* heapExtractMin();

	void PrimMST();
	void PrimMSTArray();
	void build();
	void showResult(double time);
	void showResultArray(double time);

	void debug();

	/*Functions needed for Kruskal's algorithm*/
	void Kruskal1();
	void Kruskal2();
};

#endif
		 