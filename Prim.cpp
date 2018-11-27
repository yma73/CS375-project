#include "Graph.h"

using namespace std;

Graph::Graph(string filename){
	ifstream myfile (filename);
	string line;
	getline(myfile,line);
	v_num = stoi(line,NULL,10);
	while(getline(myfile,line)){
		vector<int> e = stringSplit(line);
		if(e.size() != 3){
			perror("Wrong input format!");
			exit(1);
		}
		edges.push_back(Edge{e[0],e[1],e[2]});
	}
	myfile.close();
}

vector<int> Graph::stringSplit(string s){
	istringstream iss(s);
  	vector<int> retVal;
  	string i;
  	while(iss >> i) {
    	retVal.push_back(stoi(i,NULL,10));
  	}
  	return retVal;
}

void Graph::print(){
	cout << "Num of vertices: " << v_num << endl;
	if(edges.size() == 0){
		cout << "This graph contains no edges!" << endl;
	}
	for(size_t i = 0; i < edges.size(); i ++){
		cout << "Edge# " << i <<" connects " << edges[i].start << " with " << edges[i].end << " with a weight: " << edges[i].weight << endl; 
	}
}

void Graph::PrimMST(){
	build();
	//debug();
	heapDecreaseKey(1,0);
	while(!isEmpty()){
		Node * u;
		#if 1
		u = heapExtractMin();
		#else
		u = arrayExtractMin();
		#endif 
		for(size_t i = 0; i < u->adj.size(); i ++){
			Node* v = findNode(u->adj[i].end);
			if(v != NULL && u->adj[i].weight < v->key){
				v->parent = u->id;
				heapDecreaseKey(v->id,u->adj[i].weight);
			}
		}
	}

}

void Graph::showResult(){
	//debug();
	ofstream myfile;
	myfile.open("mstPrim.txt", ios::out);
	for(size_t i = 0; i < nodes.size(); i ++){
		//cout << "Node#: " << i << "\nTree edges related to this node:" << endl;
		//cout << "parent: " << nodes[i]->parent << endl;
		for(size_t j = 0; j < nodes[i]->adj.size(); j ++){
		//	cout << j << " : " << nodes[i]->adj[j].end << endl;
			if(nodes[i]->parent == nodes[i]->adj[j].end){
				myfile << "An tree edge from " << nodes[i]->adj[j].end << " to " << i << '\n';
			}
		}
	}
	myfile.close();
}

void Graph::build(){
	Node* empty = new Node;
	empty->id = -1;
	empty->key = -1;
	empty->parent = -1;
	non_tree_nodes.push_back(empty);
	for(int i = 0; i <= v_num; i ++){
		handles.push_back(-1);
	}
	for(int id = 0; id < v_num; id ++){
		Node* newNode = new Node;
		newNode->id = id;
		newNode->key = INT_MAX;
		newNode->parent = -1;
		for(size_t i = 0; i < edges.size(); i ++){
			if(edges[i].start == id){
				newNode->adj.push_back(edges[i]);
			}else if(edges[i].end == id){
				Edge e = {edges[i].end,edges[i].weight,edges[i].start};
				newNode->adj.push_back(e);
			}
		}
		nodes.push_back(newNode);
		insertNode(id,INT_MAX);
	}
	for(size_t i = 0; i < nodes.size(); i ++){
		if(nodes[i]->adj.size() == 0){
			perror("Bad input: graph not connected");
			exit(3);
		}
	}
}

void Graph::debug(){
	for(int i = 0; i < v_num; i ++){
		cout << "Node# " << nodes[i]->id << "; Key: " << nodes[i]->key << "; Parent: " << nodes[i]->parent << "; List: " << endl;
		for(size_t j = 0; j < nodes[i]->adj.size(); j ++){
			cout << nodes[i]->adj[j].end << " ";
		}
		cout << endl;
	}
	cout << " Queue: "<< endl;
	for(size_t i = 1; i < non_tree_nodes.size(); i++){
		cout << "Node# " << non_tree_nodes[i]->id << "; Key: " << non_tree_nodes[i]->key << "; Parent: " << non_tree_nodes[i]->parent << "; List: " << non_tree_nodes[i]->adj.size() << endl;
	}
}

Graph::~Graph(){
	for(size_t i = 0; i < nodes.size(); i ++){
		delete nodes[i];
	}
}
