#include "Header.hpp"

int main()
{
	int wybor;
	do
	{
		cout << "Czy narysowac drzewo? >>>> 1 - tak, 2 - nie" << endl;
		
		cin >> wybor;
		tree tree1;
		switch (wybor)
		{
		case 1:


			tree1.insertRBT(31);
			tree1.insertRBT(24);
			tree1.insertRBT(23);
			tree1.insertRBT(12);
			tree1.insertRBT(2);
			tree1.insertRBT(9);
			tree1.insertRBT(18);
			tree1.insertRBT(13);
			tree1.insertRBT(8);
			tree1.insertRBT(3);
			tree1.insertRBT(7);
			tree1.insertRBT(33);

			tree1.paintvoid();
			tree1.displayvoid();
			break;
		case 2:
			return 0;
			break;
		default:
			cout << "Wybierz wlasciwy numer:" << endl;
			cin.clear();
			cin.get();
		}
	} 
	while (1);

	
	return 0;
}