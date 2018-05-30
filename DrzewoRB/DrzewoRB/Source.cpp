#include "Header.hpp"


tree::tree() //konstruktor drzewa, opisanie straznika
{
	Sentinel.left = &Sentinel;
	Sentinel.right = &Sentinel;
	Sentinel.up = &Sentinel;
	Sentinel.color = 'B';
	root = &Sentinel;

	DEBUG_LOG("tree - konstruktor domyslny");
}

tree::~tree() //destruktor drzewa
{
	destructTree(root);
	DEBUG_LOG("tree - destruktor");
}

void tree::destructTree(node * root) //usuwanie wszystkich wezlow drzewa
{
	if (root != &Sentinel)
	{
		destructTree(root->left);
		destructTree(root->right);
		delete root;
	}
}

void tree::rightRotation(node * ref_root) //rotacja w prawo
{
	node * node, *parent;
	node = ref_root->left;
	
	if (node != &Sentinel)
	{
		parent = ref_root->up;
		ref_root->left = node->right;
		if (ref_root->left != &Sentinel)
		{
			ref_root->left->up = ref_root;
		}
		node->right = ref_root;
		node->up = parent;
		ref_root->up = node;

		if (parent != &Sentinel)
		{
			if (parent->left == ref_root)
			{
				parent->left = node;
			}
			else parent->right = node;
		}
		else root = node;
	}
}


void tree::leftRotation(node * ref_root) //rotacja w lewo
{
	node * node, *parent;
	node = ref_root->right;
	
	if (node != &Sentinel)
	{
		parent = ref_root->up;
		ref_root->right = node->left;
		if (ref_root->right != &Sentinel)
		{
			ref_root->right->up = ref_root;
		}
		node->left = ref_root;
		node->up = parent;
		ref_root->up = node;

		if (parent != &Sentinel)
		{
			if (parent->left == ref_root)
			{
				parent->left = node;
			}
			else parent->right = node;
		}
		else root = node;
	}
}


void tree::add(int key) //dodawanie elementu
{
	node *A, *B;
	A = new node;

	A->left = &Sentinel;        
	A->right = &Sentinel;
	A->up = root;
	A->key = key;

	if (A->up == &Sentinel)
	{
		root = A;
	}
	else
		while (true)
		{
			if (key < A->up->key)
			{
				if (A->up->left == &Sentinel)
				{
					A->up->left = A;
					break;
				}
				A->up = A->up->left;
			}
			else
			{
				if (A->up->right == &Sentinel)
				{
					A->up->right = A;
					break;
				}
				A->up = A->up->right;
			}
		}
	A->color = 'R';
	while ((A != root) && (A->up->color == 'R'))
	{
		if (A->up == A->up->up->left)
		{
			B = A->up->up->right; 
			if (B->color == 'R')
			{
				A->up->color = 'B';
				B->color = 'B';
				A->up->up->color = 'R';
				A = A->up->up;
				continue;
			}
			if (A == A->up->right) 
			{
				A = A->up;
				leftRotation(A);
			}

			A->up->color = 'B'; 
			A->up->up->color = 'R';
			rightRotation(A->up->up);
			break;
		}
		else
		{                  
			B = A->up->up->left;

			if (B->color == 'R')
			{
				A->up->color = 'B';
				B->color = 'B';
				A->up->up->color = 'R';
				A = A->up->up;
				continue;
			}

			if (A == A->up->left)
			{
				A = A->up;
				rightRotation(A);
			}
			A->up->color = 'B';
			A->up->up->color = 'R';
			leftRotation(A->up->up);
			break;
		}
	}
	root->color = 'B';
}

void tree::display(struct node *root) //wyswietlanie proste
{
	if (root != &Sentinel)
	{
		display(root->left);
		cout << root->key << " " << root->color << endl;
		display(root->right);
	}
}

void tree::displayvoid() 
{
	display(root);
}

void tree::paint(struct node *root, int distance) //wyswietlanie graficzne
{
	int place = 10;

	if (root == &Sentinel)
		return;

	distance += place;
	paint(root->right, distance);

	cout << endl;
	for (int i = place; i < distance; i++)
	{
		cout << " ";
	}
	cout << root->key << " " << root->color << endl;
	paint(root->left, distance);
}

void tree::paintvoid() 
{
	paint(root, 0);
}

void tree::save(node*root) //zapisywanie do pliku
{
	ofstream out;
	out.open("save.txt", ios::out | ios::app);
	if (root != &Sentinel)
	{
		save(root->left);
		out << root->key << " " << root->color << "    ";
		save(root->right);

	}
	out.close();
}

void tree::savevoid()
{
	save(root);
}