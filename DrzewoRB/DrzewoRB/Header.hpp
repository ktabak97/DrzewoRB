#pragma once
#ifndef HEADER_HPP
#define HEADER_HPP
#ifdef _DEBUG
#define DEBUG_LOG(a) cout << __FILE__ << "(" << __LINE__ << "): " << a << endl;
#else
#define DEBUG_LOG(a)
#endif


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

	tree();             // Konstruktor klasy
	~tree();            // Destruktor klasy

	void destructTree(node * p); // Usuwa rekurencyjnie drzewo
	node * findRBT(int k); // Wyszukuje w�ze� o kluczu k
	node * minRBT(node * p); // Wyszukuje najmniejszy w�ze� w p
	node * succRBT(node * p);// Wyszukuje nast�pnik p
	void rot_L(node * A); // Rotacja w lewo wzgl�dem A
	void rot_R(node * A); // Rotacja w prawo wzgl�dem A
	void insertRBT(int k);   // Wstawia w�ze� o kluczu k
	void removeRBT(node * X); // Usuwa w�ze� X
	void paint(struct node *root, int distance);
	void paintvoid();
	void display(struct node *root);
	void displayvoid();
};


#endif HEADER_HPP// _DEBUG