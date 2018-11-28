#ifndef DISJOINTSET2_H
#define DISJOINTSET2_H
#include<map>


struct Item;

struct Node2{
	int val;
	Node2 *next;
	Item *itemPtr;
};

struct Item{
	Node2 *head, *tail;
	int length;
};

class DisjointSet2{
private:
	std::map<int, Node2*> nodeAddress;
public:
	DisjointSet2(int n);
	void makeset(int a);
	Item * find(int key);
	void unionSet(Item* a, Item* b);
};

#endif