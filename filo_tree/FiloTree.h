#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>

#ifndef NODE_H
#define NODE_H
class node{ 
public:
    char *name;
    int ndx;
	node *left, *right;
	~node();
	node(char *n);
	node(node *l, node *r, int index);
	void printnode();
	node();
};

#endif
#ifndef FILOTREE_H
#define FILOTREE_H
class FiloTree{
private:
	int num;
	node *root;
	double dist[50][50];
	node leaves[50];
public:
	FiloTree(char *fileName);
	~FiloTree();
	void dump() const;
	void reconstruct(node *n1, node *n2, int ndx, int ndx2, int index);
	static void compare(const FiloTree &A, const FiloTree &B);
	int findMin(double d[50][50], int num);
};

#endif
