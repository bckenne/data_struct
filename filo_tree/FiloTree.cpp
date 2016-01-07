#include "FiloTree.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
int main(int argc, char *argv[]){
	FiloTree tree(argv[1]);
	tree.dump();
}
node::node(node *l, node *r, int index){
	if(l->ndx<r->ndx){
		left=l;
		right=r;
	}
	else{
		left=r;
		right=l;
	}
	ndx=index;
}
node::node(char *n){
	name = n;
	ndx = -1;
}

node::node(){
}
node::~node(){
	if(left!=NULL)delete left;
	if(right!=NULL)delete right;
}
void node::printnode(){
	if(ndx>0)cout<<ndx<<endl;
	if(ndx==-1)cout<<name;
	if(left!=NULL){
		cout<<"...";
		left->printnode();
	}
	if(right!=NULL){
		cout<<"...";
		right->printnode();
	}
}
FiloTree::~FiloTree(){
	delete root;
}	
FiloTree::FiloTree(char *fileName){
	std::ifstream file(fileName);
	file>>num;
	for(int	 x=0;x<num;x++){
		file>>leaves[x].name;
		leaves[x].ndx=x;
	}
	for(int x=0;x<num;x++)for(int y=0;y<num;y++)file>>dist[x][y];
	int min;
	int count=1;
	while(num>1){
		min=findMin(dist,num);
		reconstruct(&leaves[min%10],&leaves[(min-(min%10))/10],min%10,(min-(min%10))/10,count);
		count++;
	}
	root = &leaves[0];
}

void FiloTree::reconstruct(node *n1, node *n2, int ndx1, int ndx2, int index){
	node newnode(n1,n2, index);
	for(int x=0;x<num;x++)dist[x][ndx1]=dist[ndx1][x]=(dist[x][ndx1]+dist[x][ndx2])/2;
	for(int x=ndx2;x<num;x++) leaves[x]=leaves[x+1];
	for(int x=0;x<num-1;x++)for(int y=ndx2;y<num-1;y++)dist[x][y]=dist[x][y+1];	
	for(int y=0;y<num-1;y++)for(int x=ndx2;x<num-1;x++)dist[x][y]=dist[x+1][y];
	dist[ndx1][ndx1]=0;
	num-=1;
	leaves[ndx1]=newnode;
}
	
int FiloTree::findMin(double d[50][50], int num){
	int min=d[0][1];
	for(int a=0;a<2;a++){
		for(int x=0;x<num;x++){
			for(int y=0;y<num;y++){
				if(a==0&&x!=y&&d[x][y]<min)min = d[x][y];
				if(a==1&&min==d[x][y]){
					if(y<x)return 10*x+y;
					else return 10*y+x;
				}
			}
		}
	}
	return 0;
}

void FiloTree::dump() const{
	root->printnode();
}
