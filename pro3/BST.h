#pragma once
#ifndef BST_H_
#define BST_H_
#include<iostream>
#include "Setting.h"


class BST {
private:
	struct node {
		Setting* data;
		node* left;
		node* right;
	};

	node* root;
	void InsertNodePrivate(Setting* data, node* ptr);
	void SaveDataOfNodesPrivate(node* ptr, ofstream& file);
	node* searchNodeInKeyPrivate(string key, node* ptr);
	int sizeTreePrivate(node* ptr);
	void inorder_print(int type, node* leaf);
	void searchNodeInnamePrivate(string name, node* ptr);
	vector<node*> v;
public:
	BST();
	~BST();
	node* createLeaf(Setting* data);
	void InsertNode(Setting* data);
	void SaveDataOfNodes();
	node* searchNodeInKey(string key);
	vector<node*> searchNodeInName(string name);
	int sizeTree();
	void inorder_print(int type);

};
#endif // !BST_H_


