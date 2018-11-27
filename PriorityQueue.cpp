#include "Graph.h"

using namespace std;


Node* Graph::findNode(int id){
	int pos = handles[id];
	if(pos == -1){
		return NULL;
	}
	return non_tree_nodes[pos]; 
}

void Graph::insertNode(int id, int w){
	int pos = (int)non_tree_nodes.size();
	if(handles[id] != -1){
		perror("This node is already in the queue!");
		return;
	}
	if(pos - 1 >= v_num){
		return;
	}

	non_tree_nodes.push_back(nodes[id]);
	handles[id] = pos;

	heapDecreaseKey(pos,w);
}

void Graph::minHeapify(int i){
	if(i == 0) return;
	int lchild = left(i);
	int rchild = right(i);
	int smallest = i;
	if(lchild <= (int)(non_tree_nodes.size()-1) && non_tree_nodes[lchild]->key < non_tree_nodes[i]->key) smallest = lchild;
	if(rchild <= (int)(non_tree_nodes.size()-1) && non_tree_nodes[rchild]->key < non_tree_nodes[smallest]->key) smallest = rchild;
	if(smallest != i){
		Node* temp_ptr = non_tree_nodes[i];
		non_tree_nodes[i] = non_tree_nodes[smallest];
		non_tree_nodes[smallest] = temp_ptr;
		int temp = handles[i];
		handles[i] = handles[smallest];
		handles[smallest] = temp;
		minHeapify(smallest);
	}
}

bool Graph::isEmpty(){
	if(non_tree_nodes.size() < 2) return true;
	return false;
}

int Graph::right(int i){
	return i*2 + 1;
}

int Graph::left(int i){
	return i*2;
}

int Graph::parent(int i){
	return i/2;
}

Node* Graph::heapExtractMin(){
	Node* min = non_tree_nodes[1];
	non_tree_nodes[1] = non_tree_nodes[non_tree_nodes.size() - 1];
	non_tree_nodes.pop_back();
	minHeapify(1);
	return min;
}

void Graph::heapDecreaseKey(int pos, int key){
	if(key >= non_tree_nodes[pos]->key) return;
	non_tree_nodes[pos]->key = key;
	while(pos > 1 && non_tree_nodes[parent(pos)]->key > non_tree_nodes[pos]->key){
		int parent_pos = parent(pos);
		Node* temp = non_tree_nodes[pos];
		non_tree_nodes[pos] = non_tree_nodes[parent_pos];
		non_tree_nodes[parent_pos] = temp;
		pos = parent_pos;
	}
}

/*
Node Graph::arrayExtractMin(){
	
}*/