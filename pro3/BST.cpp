#include "BST.h"
#include<iostream>
#include<sstream>
#include<string>
#include<fstream>
#include<vector>


BST::BST() {
	root = nullptr;
}

BST::~BST() {
}

BST::node* BST::createLeaf(Setting* data) {
	node* n = new node;
	n->data = data;
	n->left = nullptr;
	n->right = nullptr;
	return n;
}

void BST::InsertNode(Setting* data) {
	InsertNodePrivate(data, root);
}

void BST::InsertNodePrivate(Setting* data, node* ptr) {
	string name_data = "";
	string node_data = "";
	if (ptr != nullptr) {
		name_data = data->getPersonalKey();
		node_data = ptr->data->getPersonalKey();;
	}
	if (root == nullptr) {
		root = createLeaf(data);
	}
	else if (name_data.compare(node_data) < 0) {
		if (ptr->left != nullptr) {
			InsertNodePrivate(data, ptr->left);
		}
		else {
			ptr->left = createLeaf(data);
		}
	}
	else if (name_data.compare(node_data) > 0) {
		if (ptr->right != nullptr) {
			InsertNodePrivate(data, ptr->right);
		}
		else {
			ptr->right = createLeaf(data);
		}
	}
	else {
		cout << "Data has already been added to the tree\n";
	}
}

void BST::SaveDataOfNodes() {
	ofstream file1("Setting.txt");
	try {
		if (file1.is_open()) {
			SaveDataOfNodesPrivate(root, file1);
		}
		else {
			throw exception();	//throw out the warning
		}
	}
	catch (const exception& e) {
		cerr << "Unable to open file to write " << "Setting.txt" << endl;
	}

}

void BST::SaveDataOfNodesPrivate(node* ptr, ofstream& file) {
	if (root != nullptr) {
		if (ptr->left != nullptr) {
			SaveDataOfNodesPrivate(ptr->left, file);
		}
		file << ptr->data->toStringSetting() << ptr->data->getGeneral()->toStringGeneral()
			<< ptr->data->getSound()->toStringSound() << ptr->data->getDisplay()->toStringDisplay() << endl;
		if (ptr->right != nullptr) {
			SaveDataOfNodesPrivate(ptr->right, file);
		}
	}
	else {
		cout << "the tree is empty\n";
	}
}

BST::node* BST::searchNodeInKey(string key) {
	return searchNodeInKeyPrivate(key, root);
}

BST::node* BST::searchNodeInKeyPrivate(string key, node* ptr) {
	if (ptr != nullptr) {
		if (ptr->data->getPersonalKey() == key) {
			return ptr;
		}
		else {
			if (key < ptr->data->getPersonalKey()) {
				return searchNodeInKeyPrivate(key, ptr->left);
			}
			else {
				return searchNodeInKeyPrivate(key, ptr->right);
			}
		}
	}
	else {
		return nullptr;
	}
}

int BST::sizeTree() {
	return sizeTreePrivate(root);
}
int BST::sizeTreePrivate(node* ptr) {
	if (ptr == nullptr)
		return 0;
	else
		return(sizeTreePrivate(ptr->left) + 1 + sizeTreePrivate(ptr->right));
}

//in trung to LNR
void BST::inorder_print(int type) {
	inorder_print(type, root);
	cout << "\n";
}

void BST::inorder_print(int type, node* leaf) {
	if (leaf != nullptr) {
		switch (type)
		{
		case 1:
			inorder_print(1, leaf->left);
			leaf->data->xuatThongTin();
			leaf->data->getGeneral()->xuatThongTin_General();
			cout << endl;
			inorder_print(1, leaf->right);
			break;
		case 2:
			inorder_print(2, leaf->left);
			leaf->data->xuatThongTin();
			leaf->data->getSound()->xuatThongTin_Sound();
			cout << endl;
			inorder_print(2, leaf->right);
			break;
		case 3:
			inorder_print(3, leaf->left);
			leaf->data->xuatThongTin();
			leaf->data->getDisplay()->xuatThongTin_Display();
			cout << endl;
			inorder_print(3, leaf->right);
			break;
		case 4:
			inorder_print(4, leaf->left);
			leaf->data->xuatThongTin();
			leaf->data->getDisplay()->xuatThongTin_Display();
			leaf->data->getSound()->xuatThongTin_Sound();
			leaf->data->getGeneral()->xuatThongTin_General();
			cout << endl;
			inorder_print(4, leaf->right);
		default:
			break;
		}
	}
}

vector<BST::node*> BST::searchNodeInName(string name) {
	v.clear();
	searchNodeInnamePrivate(name, root);
	return v;
}

void BST::searchNodeInnamePrivate(string name, node* ptr) {

	if (ptr != nullptr) {
		if (ptr->data->getCarName() == name) {
			v.push_back(ptr);
		}
		searchNodeInnamePrivate(name, ptr->left);
		searchNodeInnamePrivate(name, ptr->right);
	}
}
