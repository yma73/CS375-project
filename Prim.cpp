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
		cout << "Edge#i connects " << edges[i].start << " with " << edges[i].end << " with a weight: " << edges[i].weight << endl; 
	}
}