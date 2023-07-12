#include "A5(3) Header.h";

int main()
{
	list<phone> li;
	phone p;										//taking objects of list and phone for performing operations
	fstream file ("data.bin", ios::in | ios::binary);						//opening file in read mode
	if (file) {
		cout << "File opened successfully!\nDisplaying Data Of Mobile Phones:\n\n";
		open(file, p, li);												//if file opened then calling open function
		operations(file,p,li);											//and operations function to perform operations
	}
	else {
		file.open("data.bin", ios::app | ios::binary);					//else creating a file
		cout << "File created successfully!\n";		
		cout << "You can perform differernt operations on File here!\n";
		operations(file, p, li);										//and performing different operations on it
	}
	file.close();
	cout << "\n\t\tThanks For Using!\n\n";
	system("PAUSE");
	return 0;
}