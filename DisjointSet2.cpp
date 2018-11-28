#include<iostream>
#include "DisjointSet2.h"

DisjointSet2::DisjointSet2(int n){
	for(int i=0;i<n;i++){
		makeset(i);
	}
}
void DisjointSet2::makeset(int a){
	Item * newSet =new Item;
	newSet->head =new Node2;
	newSet->tail=newSet->head;
	newSet->length=1;

	nodeAddress[a]=newSet->head;

	newSet->head->val=a;
	newSet->head->itemPtr=newSet;
	newSet->head->next=NULL;
}

Item* DisjointSet2::find(int key){
	Node2 * p=nodeAddress[key];
	return p->itemPtr;
}

void DisjointSet2::unionSet(Item* a, Item* b){
	Node2 *temp1=a->head;
	Node2 *temp2=b->head;

	if(a->length<b->length){
		while(temp1!=NULL){
			temp1->itemPtr=b;
			temp1=temp1->next;
		}
		b->tail->next=a->head;
		b->tail=a->tail;
		b->length+=a->length;
		delete a;
	}
	else{
		while(temp2!=NULL){
			temp2->itemPtr=a;
			temp2=temp2->next;
		}
		a->tail->next=b->head;
		a->tail=b->tail;
		a->length+=b->length;
		delete b;
	}
}