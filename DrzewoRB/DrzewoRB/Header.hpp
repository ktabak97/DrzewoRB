#pragma once
#ifndef HEADER_HPP
#define HEADER_HPP
#ifdef _DEBUG
#define DEBUG_LOG(a) cout << __FILE__ << "(" << __LINE__ << "): " << a << endl <<endl;
#else
#define DEBUG_LOG(a)
#endif

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

struct node
{
	node * left;
	node * right;
	node * up;
	int key;
	char color;
};

class tree
{
public:
	node * root;
	node Sentinel;

	tree();
	~tree();
	void destructTree(node * root);
	
	void rightRotation(node * root);
	void leftRotation(node * root);
	void add(int key);
	void paint(struct node *root, int distance);
	void paintvoid();
	void display(struct node *root);
	void displayvoid();
	void save(node *root);
	void savevoid();
};


#endif HEADER_HPP// _DEBUG