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
	clock_t t_start,t_end;
	t_start=clock();
	/*initialization*/
	Node* empty = new Node;
	empty->id = -1;
	empty->key = -1;
	empty->parent = -1;
	non_tree_nodes.push_back(empty);
	for(int i = 0; i <= v_num; i ++){
		handles.push_back(-1);
	}
	for(size_t i = 0; i < nodes.size(); i ++){
		insertNode(nodes[i]->id,INT_MAX);
	}
	/*Start*/
	#if HANDLE == 1
	heapDecreaseKey(1,0);
	#else
	int index = findNodeIndex(0);
	heapDecreaseKey(index,0);
	#endif
	while(!isEmpty()){
		Node * u;
		u = heapExtractMin();
		for(size_t i = 0; i < u->adj.size(); i ++){
			Node* v = findNodeHeap(u->adj[i].end);
	
			if(v != NULL && u->adj[i].weight < v->key){
				v->parent = u->id;
					#if HANDLE == 1
					heapDecreaseKey(handles[v->id + 1],u->adj[i].weight);
					#else
					int index = findNodeIndex(v->id);
					heapDecreaseKey(index,u->adj[i].weight);
					#endif		
			}
		}
	}
	t_end=clock();
	double time = (t_end-t_start)*1.0/CLOCKS_PER_SEC*1000;
	showResult(time);
}

void Graph::PrimMSTArray(){
	clock_t t_start,t_end;
	t_start=clock();
	/*initialization*/
	Node* empty = new Node;
	empty->id = -1;
	empty->key = -1;
	empty->parent = -1;
	non_tree_nodes.push_back(empty);
	for(int i = 0; i <= v_num; i ++){
		handles.push_back(-1);
	}
	for(size_t i = 0; i < nodes.size(); i ++){
		non_tree_nodes.push_back(nodes[i]);
	}
	/*Start*/
	arrayDecreaseKey(0,0);
	while(!isEmpty()){
		Node * u;
		#if HEAP == 1
		u = heapExtractMin();
		#else
		u = arrayExtractMin();
		#endif 
		for(size_t i = 0; i < u->adj.size(); i ++){

			Node* v = findNodeArray(u->adj[i].end);
		
			if(v != NULL && u->adj[i].weight < v->key){
				v->parent = u->id;
				arrayDecreaseKey(v->id,u->adj[i].weight);
			}
		}
	}
	t_end=clock();
	double time = (t_end-t_start)*1.0/CLOCKS_PER_SEC*1000;
	showResultArray(time);
}


void Graph::showResult(double time){
	ofstream myfile;
	myfile.open("output/prim_heap.txt", ios::out);
	int totalWeight = 0;
	int num_edges = edges.size();
	for(size_t i = 0; i < nodes.size(); i ++){
		for(size_t j = 0; j < nodes[i]->adj.size(); j ++){
			if(nodes[i]->parent == nodes[i]->adj[j].end){
				//myfile << "An tree edge from " << nodes[i]->adj[j].end << " to " << i << '\n';
				totalWeight += nodes[i]->adj[j].weight;
			//	edges ++;
			}
		}
	}
	myfile << "edges:  " << num_edges << '\n';
	myfile << "totalWeight:  " << totalWeight << '\n';
	myfile << "time:  " << time <<" ms"<<'\n';
	myfile.close();
}

void Graph::showResultArray(double time){
	ofstream myfile;
	myfile.open("output/prim_array.txt", ios::out);
	int totalWeight = 0;
	int num_edges = edges.size();
	for(size_t i = 0; i < nodes.size(); i ++){
		for(size_t j = 0; j < nodes[i]->adj.size(); j ++){
			if(nodes[i]->parent == nodes[i]->adj[j].end){
				//myfile << "An tree edge from " << nodes[i]->adj[j].end << " to " << i << '\n';
				totalWeight += nodes[i]->adj[j].weight;
	//			edges ++;
			}
		}
	}
	myfile << "edges:  " << num_edges << '\n';
	myfile << "totalWeight:  " << totalWeight << '\n';
	myfile << "time:  " << time <<" ms"<<'\n';
	myfile.close();

}


void Graph::build(){
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
			cout << "To: " << nodes[i]->adj[j].end << "; weight: " << nodes[i]->adj[j].weight << " ";
		}
		//cout << endl;
	}
	/*cout << " Queue: "<< endl;
	for(size_t i = 1; i < non_tree_nodes.size(); i++){
		cout << "Node# " << non_tree_nodes[i]->id << "; Key: " << non_tree_nodes[i]->key << "; Parent: " << non_tree_nodes[i]->parent << "; List: " << non_tree_nodes[i]->adj.size() << endl;
	}
	cout << "Handles: " << endl;
	for(size_t i = 1; i < handles.size(); i++){
		cout << "Node# " << i-1 << " resides in " << handles[i] << endl;
	}*/
}

Graph::~Graph(){
	for(size_t i = 0; i < nodes.size(); i ++){
		delete nodes[i];
	}
}
