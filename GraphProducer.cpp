#include<iostream>
#include<cmath>
#include<ctime>
#include<cstdlib>
#include<fstream>

using namespace std;
 
#define MAX_VERTICES 5000 


typedef int vertex_type;
typedef int edge_type;

struct Graph{
    vertex_type V[MAX_VERTICES] = {-1};//the set of vertices
    edge_type E[MAX_VERTICES][MAX_VERTICES];//the set of edges
    int v_num;//the number of vertices
    int e_num;//the number of edges
};
 
/*Randomize the vertice id [1, 100]*/
int randomNumV(int v){
    int r;
   	//srand(time(NULL));//random seeds
    r = rand()%v;
    return r;
}

/*Randomize the weight: [1,10]*/
edge_type randomNumW(){
    edge_type r;
     //srand(time(NULL));//random seeds
    r = rand()%10 + 1;
    return r;
}

void writeGraph(Graph *G, string filename){
	ofstream myfile;
	myfile.open(filename,ios::out);
	myfile << G->v_num << endl;
 	for(int i = 0; i < G->v_num; i++){
		for(int j = 0; j < G->v_num; j++){
 			if(i < j && G->E[i][j] != 0){
 				myfile << i << " " << G->E[i][j] << " " << j <<'\n';
			}
		}
	}
	myfile.close();
}

void createGraph(Graph *G){
	/*Set vertices for G*/
	for(int i = 0; i < G->v_num; i++){
		G->V[i]=i;
	}

	/*Set edges for G*/
	for(int i = 0; i < G->v_num; i++){
		for(int j = 0; j < G->v_num; j++){
			G->E[i][j] = 0;
		}
	}
	
	for(int k = 0; k < G->e_num; k++){
		/*randomize two different vertices*/
		int i, j;
		do{
			i = randomNumV(G->v_num);
			j = randomNumV(G->v_num);
		}while(i == j);
		//cout<<i<<" "<<j<<"\t";
		edge_type weight = randomNumW();
 		G->E[i][j] = weight;
		G->E[j][i] = weight;
	}
}
 
bool checkConnected(Graph* G){
	for(int i = 0; i < G->v_num; i ++){
		bool flag = false;
		for(int j = 0; j < G->v_num; j ++){
			if(G->E[i][j] > 0){
				flag = true;
			}
		}
		if(!flag) return false;
	}
	return true;
}

void mostSparse(Graph* G){
	/*Set vertices for G*/
	for(int i = 0; i < G->v_num; i++){
		G->V[i]=i;
	}

	/*Set edges for G*/
	for(int i = 0; i < G->v_num; i++){
		for(int j = 0; j < G->v_num; j++){
			G->E[i][j] = 0;
		}
	}

	int i = 0;
	int j = 1;
	
	for(int k = 0; k < G->e_num-1; k++){
		edge_type weight = randomNumW();
 		G->E[i][j] = weight;
		G->E[j][i] = weight;
		i++;
		j++;
	}
}

void mostDense(Graph* G){
	/*Set vertices for G*/
	for(int i = 0; i < G->v_num; i++){
		G->V[i]=i;
	}

	/*Set edges for G*/
	for(int i = 0; i < G->v_num; i++){
		for(int j = 0; j < G->v_num; j++){
			G->E[i][j] = 0;
		}
	}
	
	 for(int i = 0; i < G->v_num; i++){
		for(int j = i + 1; j < G->v_num; j++){
 			edge_type weight = randomNumW();
 			G->E[i][j] = weight;
			G->E[j][i] = weight;
		}
	}
}

int main(int argc, char** argv){
	if(argc != 4){
		perror("please invoke as: ./GraphProducer vertice_num edge_num!");
		exit(1);
	}

	int v_num = stoi(argv[1],NULL,10);
	int e_num = stoi(argv[2],NULL,10);

	Graph* graph = new Graph;
	graph->v_num = v_num;
	graph->e_num = e_num;

	if(v_num == e_num){
		mostSparse(graph);
	}else if(e_num == (v_num*(v_num-1))/2){
		mostDense(graph);
	}else{
		bool check = false;
		while(!check){
			createGraph(graph);
			check = checkConnected(graph);
		}
	}	

	writeGraph(graph,argv[3]);

	delete graph;

    return 0;
}