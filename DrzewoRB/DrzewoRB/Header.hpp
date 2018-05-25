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
	node * findRBT(int k); // Wyszukuje wêze³ o kluczu k
	node * minRBT(node * p); // Wyszukuje najmniejszy wêze³ w p
	node * succRBT(node * p);// Wyszukuje nastêpnik p
	void rot_L(node * A); // Rotacja w lewo wzglêdem A
	void rot_R(node * A); // Rotacja w prawo wzglêdem A
	void insertRBT(int k);   // Wstawia wêze³ o kluczu k
	void removeRBT(node * X); // Usuwa wêze³ X
	void paint(struct node *root, int distance);
	void paintvoid();
	void display(struct node *root);
	void displayvoid();
};


#endif HEADER_HPP// _DEBUG