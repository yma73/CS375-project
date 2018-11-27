#ifndef DISJOINTSET2_H
#define DISJOINTSET2_H
#include<map>


struct Item;

struct Node{
	int val;
	Node *next;
	Item *itemPtr;
};

struct Item{
	Node *head, *tail;
	int length;
};

class DisjointSet2{
private:
	std::map<int, Node*> nodeAddress;
public:
	DisjointSet2(int n);
	void makeset(int a);
	Item * find(int key);
	void unionSet(Item* a, Item* b);
};

#endif