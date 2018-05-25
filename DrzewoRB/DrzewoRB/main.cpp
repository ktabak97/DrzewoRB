#include "Header.hpp"



int main()
{
	int wybor;
	do
	{
		cout << "Czy narysowac drzewo? >>>> 1 - tak, 2 - nie" << endl;
		
		cin >> wybor;
		tree tree1;
		ifstream input;
		input.open("data.txt");
		
		switch (wybor)
		{
		case 1:
			int liczba;
			while (input >> liczba)
			{
				tree1.add(liczba);
			}
			tree1.add(777);
			tree1.paintvoid();
			tree1.displayvoid();
			tree1.savevoid();
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