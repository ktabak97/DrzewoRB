#include "Header.hpp"


tree::tree()
{
	Sentinel.left = &Sentinel;
	Sentinel.right = &Sentinel;
	Sentinel.up = &Sentinel;
	Sentinel.color = 'B';
	root = &Sentinel;

	DEBUG_LOG("tree - konstruktor domyslny");
}

tree::~tree()
{
	destructTree(root);
	DEBUG_LOG("tree - destruktor");
}

void tree::destructTree(node * root)
{
	if (root != &Sentinel)
	{
		destructTree(root->left);
		destructTree(root->right);
		delete root;
	}
}

void tree::display(struct node *root)
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

void tree::paint(struct node *root, int distance)
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

// Wyszukuje wêze³ o kluczu k
// Jeœli wêze³ nie zostanie znaleziony, to zwraca
// wskazanie puste NULL
//-----------------------------------------------
node * tree::findRBT(int k)
{
	node * p;

	p = root;
	while ((p != &Sentinel) && (p->key != k))
		if (k < p->key) p = p->left;
		else           p = p->right;
		if (p == &Sentinel) return NULL;
		return p;
}

// Wyszukuje najmniejszy wêze³ w poddrzewie
// o korzeniu p
//-----------------------------------------
node * tree::minRBT(node * p)
{
	if (p != &Sentinel)
		while (p->left != &Sentinel) p = p->left;
	return p;
}

// Zwraca nastêpnik p
//-------------------
node * tree::succRBT(node * p)
{
	node * r;

	if (p != &Sentinel)
	{
		if (p->right != &Sentinel) return minRBT(p->right);
		else
		{
			r = p->up;
			while ((r != &Sentinel) && (p == r->right))
			{
				p = r;
				r = r->up;
			}
			return r;
		}
	}
	return &Sentinel;
}

// Wykonuje rotacjê w lewo wzglêdem A
//-----------------------------------
void tree::rot_L(node * A)
{
	node * B, *p;

	B = A->right;
	if (B != &Sentinel)
	{
		p = A->up;
		A->right = B->left;
		if (A->right != &Sentinel) A->right->up = A;

		B->left = A;
		B->up = p;
		A->up = B;

		if (p != &Sentinel)
		{
			if (p->left == A) p->left = B; else p->right = B;
		}
		else root = B;
	}
}

// Wykonuje rotacjê w prawo wzglêdem A
//------------------------------------
void tree::rot_R(node * A)
{
	node * B, *p;

	B = A->left;
	if (B != &Sentinel)
	{
		p = A->up;
		A->left = B->right;
		if (A->left != &Sentinel) A->left->up = A;

		B->right = A;
		B->up = p;
		A->up = B;

		if (p != &Sentinel)
		{
			if (p->left == A) p->left = B; else p->right = B;
		}
		else root = B;
	}
}

// Wstawia do drzewa wêze³ o kluczu k
//-----------------------------------
void tree::insertRBT(int k)
{
	node * X, *Y;

	X = new node;        // Tworzymy nowy wêze³
	X->left = &Sentinel;          // Inicjujemy pola
	X->right = &Sentinel;
	X->up = root;
	X->key = k;
	if (X->up == &Sentinel) root = X; // X staje siê korzeniem
	else
		while (true)             // Szukamy liœcia do zast¹pienia przez X
		{
			if (k < X->up->key)
			{
				if (X->up->left == &Sentinel)
				{
					X->up->left = X;  // X zastêpuje lewy liœæ
					break;
				}
				X->up = X->up->left;
			}
			else
			{
				if (X->up->right == &Sentinel)
				{
					X->up->right = X; // X zastêpuje prawy liœæ
					break;
				}
				X->up = X->up->right;
			}
		}
	X->color = 'R';         // Wêze³ kolorujemy na czerwono
	while ((X != root) && (X->up->color == 'R'))
	{
		if (X->up == X->up->up->left)
		{
			Y = X->up->up->right; // Y -> wujek X

			if (Y->color == 'R')  // Przypadek 1
			{
				X->up->color = 'B';
				Y->color = 'B';
				X->up->up->color = 'R';
				X = X->up->up;
				continue;
			}

			if (X == X->up->right) // Przypadek 2
			{
				X = X->up;
				rot_L(X);
			}

			X->up->color = 'B'; // Przypadek 3
			X->up->up->color = 'R';
			rot_R(X->up->up);
			break;
		}
		else
		{                  // Przypadki lustrzane
			Y = X->up->up->left;

			if (Y->color == 'R') // Przypadek 1
			{
				X->up->color = 'B';
				Y->color = 'B';
				X->up->up->color = 'R';
				X = X->up->up;
				continue;
			}

			if (X == X->up->left) // Przypadek 2
			{
				X = X->up;
				rot_R(X);
			}

			X->up->color = 'B'; // Przypadek 3
			X->up->up->color = 'R';
			rot_L(X->up->up);
			break;
		}
	}
	root->color = 'B';
}

// Usuwa z drzewa wêze³ X
//-----------------------
void tree::removeRBT(node * X)
{
	node * W, *Y, *Z;

	if ((X->left == &Sentinel) || (X->right == &Sentinel)) Y = X;
	else                                    Y = succRBT(X);

	if (Y->left != &Sentinel) Z = Y->left;
	else              Z = Y->right;

	Z->up = Y->up;

	if (Y->up == &Sentinel) root = Z;
	else if (Y == Y->up->left) Y->up->left = Z;
	else                      Y->up->right = Z;

	if (Y != X) X->key = Y->key;

	if (Y->color == 'B')   // Naprawa struktury drzewa czerwono-czarnego
		while ((Z != root) && (Z->color == 'B'))
			if (Z == Z->up->left)
			{
				W = Z->up->right;

				if (W->color == 'R')
				{              // Przypadek 1
					W->color = 'B';
					Z->up->color = 'R';
					rot_L(Z->up);
					W = Z->up->right;
				}

				if ((W->left->color == 'B') && (W->right->color == 'B'))
				{              // Przypadek 2
					W->color = 'R';
					Z = Z->up;
					continue;
				}

				if (W->right->color == 'B')
				{              // Przypadek 3
					W->left->color = 'B';
					W->color = 'R';
					rot_R(W);
					W = Z->up->right;
				}

				W->color = Z->up->color; // Przypadek 4
				Z->up->color = 'B';
				W->right->color = 'B';
				rot_L(Z->up);
				Z = root;         // To spowoduje zakoñczenie pêtli
			}
			else
			{                // Przypadki lustrzane
				W = Z->up->left;

				if (W->color == 'R')
				{              // Przypadek 1
					W->color = 'B';
					Z->up->color = 'R';
					rot_R(Z->up);
					W = Z->up->left;
				}

				if ((W->left->color == 'B') && (W->right->color == 'B'))
				{              // Przypadek 2
					W->color = 'R';
					Z = Z->up;
					continue;
				}

				if (W->left->color == 'B')
				{              // Przypadek 3
					W->right->color = 'B';
					W->color = 'R';
					rot_L(W);
					W = Z->up->left;
				}

				W->color = Z->up->color;  // Przypadek 4
				Z->up->color = 'B';
				W->left->color = 'B';
				rot_R(Z->up);
				Z = root;         // To spowoduje zakoñczenie pêtli
			}

	Z->color = 'B';

	delete Y;
}
