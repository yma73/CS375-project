#include "Graph.h"
#include "DisjointSet.h"
#include "DisjointSet2.h"


using namespace std;

/*typedef struct{
	int start;
	int weight;
	int end;
}Edge;
*/
void QuickSort(vector<Edge *> *edges_k, int p, int r);
int Partition(vector<Edge *> *edges_k, int p, int r);
void Kruskal1();
void Kruskal2();
/*
vector<Edge> edges;
int v_num=8;

int main(){
	edges.push_back(Edge{0,6,1});
	edges.push_back(Edge{0,5,2});
	edges.push_back(Edge{0,14,4});
	edges.push_back(Edge{0,10,5});
	edges.push_back(Edge{1,4,2});
	edges.push_back(Edge{2,2,6});
	edges.push_back(Edge{2,9,3});
	edges.push_back(Edge{4,3,5});
	edges.push_back(Edge{5,8,6});
	edges.push_back(Edge{6,15,7});
	Kruskal1();
	Kruskal2();
}*/
void Graph::Kruskal1(){
	vector<Edge *> *edges_k=new vector<Edge *>();
	for(size_t i=0;i<edges.size();i++){
		Edge * e=new Edge();
		e->start=edges[i].start;
		e->weight=edges[i].weight;
		e->end=edges[i].end;

		edges_k->push_back(e);
	}

	clock_t t_start,t_end;
	t_start=clock();
	//vector<Edge> edges_k(edges);
	QuickSort(edges_k,0,edges_k->size()-1);
	vector<Edge *> * MST_edges=new vector<Edge *>();
	DisjointSet djSet(v_num);

	for(size_t i=0;i<edges_k->size();i++){
		if(djSet.find((*edges_k)[i]->start) != djSet.find((*edges_k)[i]->end)){
			MST_edges->push_back((*edges_k)[i]);
			djSet.unionSet((*edges_k)[i]->start, (*edges_k)[i]->end);
		}
	}
	t_end=clock();
	int totalWeight=0;

	ofstream myfile;
	myfile.open("mstKruskal1.txt", ios::out);
	myfile<<"Kruskal1 Implement DisjointSet by a tree structure using array"<<'\n';
	for(size_t i=0;i<MST_edges->size();i++){
		//myfile<<MST_edges[i].start<<" "<<MST_edges[i].end<<" "<<MST_edges[i].weight<<'\n';
		totalWeight+=(*MST_edges)[i]->weight;
	}
	myfile<<"totalWeight:  "<<totalWeight<<'\n';
	myfile<<"time:  "<<(t_end-t_start)*1.0/CLOCKS_PER_SEC*1000<<" ms"<<'\n';
	myfile<<'\n';
}

void Graph::Kruskal2(){
	vector<Edge *> *edges_k=new vector<Edge *>();
	for(size_t i=0;i<edges.size();i++){
		Edge * e=new Edge();
		e->start=edges[i].start;
		e->weight=edges[i].weight;
		e->end=edges[i].end;

		edges_k->push_back(e);
	}

	clock_t t_start,t_end;
	t_start=clock();
	//vector<Edge> edges_k(edges);
	QuickSort(edges_k,0,edges_k->size()-1);
	vector<Edge *> *MST_edges=new vector<Edge *>();
	DisjointSet2 djSet(v_num);

	for(size_t i=0;i<edges_k->size();i++){
		if(djSet.find((*edges_k)[i]->start) != djSet.find((*edges_k)[i]->end)){
			MST_edges->push_back((*edges_k)[i]);
			djSet.unionSet(djSet.find((*edges_k)[i]->start), djSet.find((*edges_k)[i]->end));
		}
	}
	t_end=clock();
	int totalWeight=0;
	ofstream myfile;
	myfile.open("mstKruskal2.txt", ios::out);
	myfile<<"Kruskal2 Implement DisjointSet by a linked list structure"<<'\n';
	for(size_t i=0;i<MST_edges->size();i++){
		//myfile<<MST_edges[i].start<<" "<<MST_edges[i].end<<" "<<MST_edges[i].weight<<'\n';
		totalWeight+=(*MST_edges)[i]->weight;
	}
	myfile<<"totalWeight:  "<<totalWeight<<'\n';
	myfile<<"time:  "<<(t_end-t_start)*1.0/CLOCKS_PER_SEC*1000<<" ms"<<'\n';
	myfile<<'\n';
	myfile.close();
}
void QuickSort(vector<Edge *> * edges_k, int p, int r){
	if(p<r){
		int q= Partition(edges_k,p,r);
		QuickSort(edges_k, p, q-1);
		QuickSort(edges_k, q+1, r);
	}
}

int Partition(vector<Edge *> * edges_k,int p,int r){
	Edge* x =(*edges_k)[r];
	int i=p-1;
	for(int j=p; j<=r-1; j++){
		if((*edges_k)[j]->weight<=x->weight){
			i=i+1;
			Edge * temp=(*edges_k)[i];
			(*edges_k)[i]=(*edges_k)[j];
			(*edges_k)[j]=temp;
		}
	}
	Edge * temp=(*edges_k)[i+1];
	(*edges_k)[i+1]=(*edges_k)[r];
	(*edges_k)[r]=temp;
	return i+1;
}