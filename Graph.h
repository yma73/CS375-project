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


typedef struct{
	int start;
	int weight;
	int end;
}Edge;

class DisjointSet;

class Graph{

private:
	std::vector<Edge> edges;
	int v_num;
public:
	Graph(std::string filename);
	std::vector<int> stringSplit(std::string s);
	void print();
	friend class DisjointSet;
};

#endif
		 