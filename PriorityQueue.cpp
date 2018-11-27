#include "Graph.h"

using namespace std;


Node* Graph::findNodeHeap(int id){
	id ++;
	if(id < 1 || id > v_num){
		perror("Wrong id!");
		exit(1);
	}
	int pos = handles[id];
	if(pos == -1){
		return NULL;
	}
	Node * temp = non_tree_nodes[pos];
	return temp; 
}

void Graph::insertNode(int id, int w){
	int pos = (int)non_tree_nodes.size();
	if(pos > v_num || pos < 1){
		perror("Wrong size!");
		exit(1);
	}
	if(handles[id+1] != -1){
		perror("This node is already in the queue!");
		return;
	}
	if(pos - 1 >= v_num){
		return;
	}

	non_tree_nodes.push_back(nodes[id]);
	handles[id+1] = pos;
	heapDecreaseKey(pos,w);
}

void Graph::minHeapify(int i){
	int lchild = left(i);
	int rchild = right(i);
	int smallest = i;
	if(lchild <= (int)(non_tree_nodes.size()-1) && non_tree_nodes[lchild]->key < non_tree_nodes[i]->key) smallest = lchild;
	if(rchild <= (int)(non_tree_nodes.size()-1) && non_tree_nodes[rchild]->key < non_tree_nodes[smallest]->key) smallest = rchild;
	if(smallest != i){
		int k_i = non_tree_nodes[i]->id;
		int k_smallest = non_tree_nodes[smallest]->id;
		handles[k_i+1] = smallest;
		handles[k_smallest+1] = i;

		Node* temp_ptr = non_tree_nodes[i];
		non_tree_nodes[i] = non_tree_nodes[smallest];
		non_tree_nodes[smallest] = temp_ptr;

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
	if(isEmpty()) exit(1); 
	Node* min = non_tree_nodes[1];
	non_tree_nodes[1] = non_tree_nodes[non_tree_nodes.size() - 1];
	handles[non_tree_nodes[1]->id+1] = 1;
	non_tree_nodes.pop_back();
	minHeapify(1);
	int pos = min->id + 1;
	handles[pos] = -1;
	return min;
}

void Graph::heapDecreaseKey(int pos, int key){
	if(key > non_tree_nodes[pos]->key) return;
	non_tree_nodes[pos]->key = key;
	while(pos > 1 && non_tree_nodes[parent(pos)]->key > non_tree_nodes[pos]->key){
		int parent_pos = parent(pos);
		handles[non_tree_nodes[pos]->id + 1] = parent_pos;
		handles[non_tree_nodes[parent_pos]->id + 1] = pos;
		Node* temp = non_tree_nodes[pos];
		non_tree_nodes[pos] = non_tree_nodes[parent_pos];
		non_tree_nodes[parent_pos] = temp;
		pos = parent_pos;
	}
}


Node* Graph::arrayExtractMin(){
	int min_key = INT_MAX;
	int index = 1;
	Node * min;
	for(size_t i = 1; i < non_tree_nodes.size(); i ++){
		if(non_tree_nodes[i]->key < min_key){
			min_key = non_tree_nodes[i]->key;
			min = non_tree_nodes[i];
			index = i;
		}
	}
	non_tree_nodes.erase(non_tree_nodes.begin()+index);
	return min;
}

void Graph::arrayDecreaseKey(int id, int key){
	for(size_t i = 1; i < non_tree_nodes.size(); i ++){
		if(non_tree_nodes[i]->id == id){
			if(key < non_tree_nodes[i]->key){
				non_tree_nodes[i]->key = key;
			}
			break;
		}
	}
}

Node* Graph::findNodeArray(int id){
	for(size_t i = 1; i < non_tree_nodes.size(); i ++){
		if(non_tree_nodes[i]->id == id){
			return non_tree_nodes[i];
		}
	}
	return NULL;
}