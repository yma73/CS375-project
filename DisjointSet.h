#ifndef DISJOINTSET_H
#define DISJOINTSET_H
#include<vector>

class DisjointSet{
private:
	std::vector<int> parent;
	std::vector<int> rank;
	int count;
public:
	DisjointSet(int n);
	void unionSet(int a,int b);
	int find(int x);
	int size();
};

#endif