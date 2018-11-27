#include<iostream>
#include "DisjointSet.h"

DisjointSet::DisjointSet(int n){
	count=n;
	for(int i=0;i<n;i++){
		parent.push_back(i);
		rank.push_back(1);
	}
}

void DisjointSet::unionSet(int a, int b){
	int root1 = find(a);
	int root2 = find(b);
	if(root1==root2) return;
	if(rank[root1] < rank[root2]) {
		parent[root1]=root2;
	}
	else if(rank[root2] < rank[root1]){
		 parent[root2]=root1;
	}
	else{
		parent[root1]=root2;
		rank[root2]++;
	}
	count--;
}

int DisjointSet::find(int x){
	while(x!=parent[x]){
		parent[x]=parent[parent[x]];//Path Compression
		x=parent[x];
	}
	return x;
}

int DisjointSet::size(){
	return count;
}