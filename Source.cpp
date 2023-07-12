#include "A5(3) Header.h";

ostream& operator << (ostream& out, const phone& p) {								// << operator overloading
	out << "\tPhone's ID: " << p.id << ", Phone's Maker: " << p.maker
		<< ", Phone's Model: " << p.model << "\n\tPhone's RAM: " << p.ram
		<< ", Phone's ROM: " << p.rom << ", Phone's Display Size: " << p.screen
		<< "\n\tPhone's Price: " << p.price << endl << endl;
	return out;
}

void display(const list<phone>& li) {										
	list<phone>::const_iterator it;
	int i = 1;														//displaying the data stored in
	for (it = li.begin(); it != li.end(); it++) {					//list of mobile phones
		cout << "\tRecord " << i << ":\n" << *it;					//using for loop
		i++;														//and const iterator
	}
	if (i == 1) {													//if list is empty
		cout << "\tNo Records to show!\n\n";
	}
}

void open(fstream& file, phone& p, list<phone>& li) {
	while (!file.eof())											//loop for checking end of file
	{
		file.read((char*)&p, sizeof(phone));						//reading data from the file	
		if (file.gcount() > 0) {
			li.push_front(p);										//storing data into list
		}	
	}
	display(li);													//displaying data
}

void operations(fstream& file, phone& p, list<phone>& li) {
	char ch; int choice;
	cout << "Do you want to perform any operation (Y/N): ";						//allowing user to perform operations on his choice
	cin >> ch;
	while (ch == 'y' || ch == 'Y') {
		cout << "\n\tWhich operation do you want to perform?\n\tSelect one of the following:\n";
		cout << "\t(1) ADD PHONE\n\t(2) SEARCH PHONE\n\t(3) UPDATE PHONE\n\t(4) DELETE PHONE\n\t(5) DISPLAY PHONES\n\t(6) EXIT PROGRAM\n";
		cout << "Enter your choice: ";
		cin >> choice;								//asking for user's choice
		switch (choice)								//calling different functions through switch statement 
		{											//depending upon user's choice
		case 1: addphone(p,li); break;
		case 2: searchphone(p,li); break;
		case 3: updatephone(p,li); break;
		case 4: deletephone(p,li); break;
		case 5: display(li); break;
		case 6: exit(1);
		default: cout << "Wrong choice entered!\n";
		}
		cout << "Do you want to perform another operation? (Y/N): ";
		cin >> ch;									//asking user's chooice
	}
}

void addphone(phone& p,list<phone>& li) {	
	fstream file("data.bin", ios::app | ios::binary);						//opening file in append mode
	cout << "\nPlease add necessary information about the phone!\n";		//taking inputs from user
	cout << "Enter ID of the phone: ";
	cin >> p.id;
	cout << "Enter RAM of the phone: ";
	cin >> p.ram;
	cout << "Enter ROM of the phone: ";
	cin >> p.rom;
	cout << "Enter Maker of the phone: ";
	cin >> p.maker;
	cout << "Enter Model of the phone: ";
	cin >> p.model;
	cout << "Enter Display size of the phone in inches: ";
	cin >> p.screen;
	cout << "Enter Price of the phone: ";
	cin >> p.price;
	file.write((const char*)&p, sizeof(phone));								//writing to file
	file.flush();															//flushing the data from buffer to file
	li.push_front(p);														//inserting the same data in list
	cout << p.maker << " " << p.model << " has been added to file!\n";
	file.close();
}

void addwhileupdate(phone& p)												//function for updating the record and is
{																			//only called when user is updating a record
	cout << "\nUpdating the phone...\n";
	cout << "Enter new ID of the phone: ";									//taking inputs
	cin >> p.id;;
	cout << "Enter new RAM of the phone: ";
	cin >> p.ram;
	cout << "Enter new ROM of the phone: ";
	cin >> p.rom;
	cout << "Enter new Maker of the phone: ";
	cin >> p.maker;
	cout << "Enter new Model of the phone: ";
	cin >> p.model;
	cout << "Enter new Display size of the phone in inches: ";
	cin >> p.screen;
	cout << "Enter new Price of the phone: ";
	cin >> p.price;
}

void searchbyid(const list<phone>& li) {
	list<phone>::const_iterator it;
	cout << "Enter the ID you want to search phone for: ";
	int val;
	cin >> val;														//searching the phone by id
	int i = 0;														//using iterator and loop
	for (it = li.begin(); it != li.end(); it++) {					//and comparing id using iterator pointer
		if (it->id==val) {
			i++;
			cout << "\tRecord " << i << ": \n";
			cout << *it;
		}
	}
	if (!i) {														//if no record found
		cout << "No record found!\n";
	}
}

void searchbymaker(const list<phone>& li) {
	list<phone>::const_iterator it;
	list<phone> temp;
	cout << "Enter the MAKER you want to search phone for: ";
	string val;
	cin >> val;														//searching the phone by maker
	int i = 0;														//using iterator and loop
	for (it = li.begin(); it != li.end(); it++) {
		string s = "";
		int j = 0;
		while (it->maker[j] != '\0') {								//loop for converting
			s = s + it->maker[j];									//char array to string
			j++;
		}
		if (s == val) {												//if record found
			i++;													
			cout << "\tRecord " << i << ": \n";						//displaying it
			cout << *it;
			temp.push_front(*it);									//and pushing it in temporary list for filtering
		}
	}
	if (!i) {
		cout << "No record found!\n";
	}
	else {															//filtering search results
		cout << "Do you want to filter search records? \nIf YES, select one of the options below: \n";
		cout << "\t(1)	Filter By RAM\n\t(2)	Filter By ROM\n\t(3)	Filter By DISPLAY SIZE\n\t(4)	Filter By PRICE\n";
		int ch;
		cout << "If NO, Enter 0.\n";
		cout << "Enter your choice: ";
		cin >> ch;
		switch (ch) {												//provinding different options for filtering
		case 1: searchbyram(temp); break;
		case 2: searchbyrom(temp); break;
		case 3: searchbyscreen(temp); break;
		case 4: searchbyprice(temp); break;
		case 0: return;
		default: cout << "Wrong Choice Entered!\n"; return;
		}
	}
}

void searchbymodel(const list<phone>& li) {								//same work being done as in searchbymaker
	list<phone>::const_iterator it;
	list<phone> temp;
	cout << "Enter the MODEL you want to search phone for: ";
	string val;
	cin >> val;
	int i = 0;
	for (it = li.begin(); it != li.end(); it++) {
		string s = "";
		int j = 0;
		while (it->model[j] != '\0' ) {
			s = s + it->model[j];
			j++;
		}
		if (s == val) {
			i++;
			cout << "\tRecord " << i << ": \n";
			cout << *it;
			temp.push_front(*it);
		}
	}
	if (!i) {
		cout << "No record found!\n";
	}
	else {
		cout << "Do you want to filter search records? \nIf YES, select one of the options below: \n";
		cout << "\t(1)	Filter By RAM\n\t(2)	Filter By ROM\n\t(3)	Filter By DISPLAY SIZE\n\t(4)	Filter By PRICE\n" <<
			"\t(5)	Filter By MAKER\n";
		int ch;
		cout << "If NO, Enter 0.\n";
		cout << "Enter your choice: ";
		cin >> ch;
		switch (ch) {
		case 1: searchbyram(temp); break;
		case 2: searchbyrom(temp); break;
		case 3: searchbyscreen(temp); break;
		case 4: searchbyprice(temp); break;
		case 5: searchbymaker(temp); break;
		case 0: return;
		default: cout << "Wrong Choice Entered!\n"; return;
		}
	}
}

void searchbyram(const list<phone>& li) {										//same work being done as in searchbyid
	list<phone>::const_iterator it;
	list<phone> temp;
	cout << "Enter the RAM you want to search phone for: ";
	int val;
	cin >> val;
	int i = 0;
	for (it = li.begin(); it != li.end(); it++) {
		if (it->ram == val) {
			i++;
			cout << "\tRecord " << i << ": \n";
			cout << *it;
			temp.push_front(*it);
		}
	}
	if (!i) {
		cout << "No record found!\n";
	}
	else {																	//same filter functionality as in searchbymaker
		cout << "Do you want to filter search records? \nIf YES, select one of the options below: \n";
		cout << "\t(1)	Filter By ROM\n\t(2)	Filter By DISPLAY SIZE\n\t(3)	Filter By PRICE\n" <<
			"\t(4)	Filter By MAKER\n";
		int ch;
		cout << "If NO, Enter 0,\n";
		cout << "Enter your choice: ";
		cin >> ch;
		switch (ch) {
		case 1: searchbyrom(temp); break;
		case 2: searchbyscreen(temp); break;
		case 3: searchbyprice(temp); break;
		case 4: searchbymaker(temp); break;
		case 0: return;
		default: cout << "Wrong Choice Entered!\n"; return;
		}
	}
}

void searchbyrom(const list<phone>& li) {										//same work being done as in searchbyram
	list<phone>::const_iterator it;
	list<phone> temp;
	cout << "Enter the ROM you want to search phone for: ";
	int val;
	cin >> val;
	int i = 0;
	for (it = li.begin(); it != li.end(); it++) {
		if (it->rom == val) {
			i++;
			cout << "\tRecord " << i << ": \n";
			cout << *it;
			temp.push_front(*it);
		}
	}
	if (!i) {
		cout << "No record found!\n";
	}
	else {
		cout << "Do you want to filter search records? \nIf YES, select one of the options below: \n";
		cout << "\t(1)	Filter By RAM\n\t(2)	Filter By DISPLAY SIZE\n\t(3)	Filter By PRICE\n" <<
			"\t(4)	Filter By MAKER\n";
		int ch;
		cout << "If NO, Enter 0.\n";
		cout << "Enter your choice: ";
		cin >> ch;
		switch (ch) {
		case 1: searchbyram(temp); break;
		case 2: searchbyscreen(temp); break;
		case 3: searchbyprice(temp); break;
		case 4: searchbymaker(temp); break;
		case 0: return;
		default: cout << "Wrong Choice Entered!\n"; return;
		}
	}
}

void searchbyscreen(const list<phone>& li) {										//same work being done as in searchbyram
	list<phone>::const_iterator it;
	list<phone> temp;
	cout << "Enter the DISPLAY SIZE you want to search phone for: ";
	double val;
	cin >> val;
	int i = 0;
	for (it = li.begin(); it != li.end(); it++) {
		if (it->screen == val) {
			i++;
			cout << "\tRecord " << i << ": \n";
			cout << *it;
			temp.push_front(*it);
		}
	}
	if (!i) {
		cout << "No record found!\n";
	}
	else {
		cout << "Do you want to filter search records? \nIf YES, select one of the options below: \n";
		cout << "\t(1)	Filter By RAM\n\t(2)	Filter By ROM\n\t(3)	Filter By PRICE\n" <<
			"\t(4)	Filter By MAKER\n";
		int ch;
		cout << "If NO, Enter 0.\n";
		cout << "Enter your choice: ";
		cin >> ch;
		switch (ch) {
		case 1: searchbyram(temp); break;
		case 2: searchbyrom(temp); break;
		case 3: searchbyprice(temp); break;
		case 4: searchbymaker(temp); break;
		case 0: return;
		default: cout << "Wrong Choice Entered!\n"; return;
		}
	}
}

void searchbyprice(const list<phone>& li) {										//same work being done as in searchbyram
	list<phone>::const_iterator it;
	list<phone> temp;
	cout << "Enter the PRICE you want to search phone for: ";
	double val;
	cin >> val;
	int i = 0;
	for (it = li.begin(); it != li.end(); it++) {
		if (it->price == val) {
			i++;
			cout << "\tRecord " << i << ": \n";
			cout << *it;
			temp.push_front(*it);
		}
	}
	if (!i) {
		cout << "No record found!\n";
	}
	else {
		cout << "Do you want to filter search records? \nIf YES, select one of the options below: \n";
		cout << "\t(1)	Filter By RAM\n\t(2)	Filter By ROM\n\t(3)	Filter By DISPLAY SIZE\n" <<
			"\t(4)	Filter By MAKER\n";
		int ch;
		cout << "If NO, Enter 0.\n";
		cout << "Enter your choice: ";
		cin >> ch;
		switch (ch) {
		case 1: searchbyram(temp); break;
		case 2: searchbyrom(temp); break;
		case 3: searchbyscreen(temp); break;
		case 4: searchbymaker(temp); break;
		case 0: return;
		default: cout << "Wrong Choice Entered!\n"; return;
		}
	}
}

void searchphone(const phone& p, const list<phone>& li) {
	cout << "\nYou can search any phone here!\n";
	cout << "Enter one of the options given below:\n";
	cout << "\t(1)\tSearch By ID \n\t(2)\tSearch By Maker \n\t(3)\tSearch By Model \n\t(4)\tSearch By RAM \n" <<
		"\t(5)\tSearch By ROM \n\t(6)\tSearch By Display Size \n\t(7)\tSearch By Price \n";
	cout << "Enter your choice: ";
	int choice;													//searching phone according to
	cin >> choice;												//user's choice
	switch (choice) {											//using different functions
	case 1:searchbyid(li); break;
	case 2:searchbymaker(li); break;
	case 3:searchbymodel(li); break;
	case 4:searchbyram(li); break;
	case 5:searchbyrom(li); break;
	case 6:searchbyscreen(li); break;
	case 7:searchbyprice(li); break;
	default: cout << "Wrong Choice Entered!\n";
	}
}

void updatephone(phone& p, list<phone>& li) {
	int i, fp, j = 0;													// i=phone's ID to be updated, fp=filepointer, j=variable for checking
	cout << "Here you can Update phone's record using it's ID!\n";		// whether record to be updated is found or not
	cout << "Enter ID for which you want to Update Phone: ";
	cin >> i;															// getting ID
	fstream file("data.bin", ios::in | ios::out | ios::binary);			//opening file in read, write and binary mode
	while (!file.eof())													//loop for checking end of file
	{
		fp = file.tellg();												//checking current position of file pointer
		file.read((char*)&p, sizeof(phone));							//reading data from file
		if (file.gcount() > 0) {
			if (i == p.id)													//comparing current phone's ID and ID to be updated
			{
				addwhileupdate(p);											//updating the record
				file.seekp(fp);												//moving file pointer to desired location
				file.write((const char*)&p, sizeof(phone));					//writing to the file
				j++;														//incrementing when record is updated
				break;
			}
		}
	}
	list<phone>::iterator it;
	for (it = li.begin(); it != li.end(); ++it) {									//updating the record
		if (it->id == i) {															//in the list as well
			li.erase(it);															//using iterator and built-in functions
			li.push_front(p);
			break;
		}
	}
	if (j == 0)
	{
		cout << "No record found to update associated with given ID!\n";
	}
	else
	{
		cout << "Record updated successfully!\n";
	}

	file.close();
}

void deletephone(phone& p, list<phone>& li) {
	int i, j = 0;														// i=variable for getting ID, j=variable for checking delete operation
	li.clear();															//clearing all the data from list 
	cout << "Here you can Delete record of any phone by using it's ID!\n";
	cout << "Enter ID for which you want to Delete Phone: ";
	cin >> i;															//getitng ID
	fstream file("data.bin", ios::in | ios::binary);					//opening "data.bin" file in read mode
	fstream f("temp.bin", ios::out | ios::binary);						//opening temporary file in write mode
	if (file.is_open())													//check for opened file
	{
		while (!file.eof())												//loop for checking end of file
		{
			file.read((char*)&p, sizeof(phone));						//reading data from "data.bin" file
			if (p.id != i)												//checking that phone's ID is not equal to the ID which is
			{															//desired to be deleted
				if (file.gcount() > 0)									//checking whether bytes read are greater than zero or not
				{
					f.write((const char*)&p, sizeof(phone));			//writing data to temporary file
				}
			}
			else
			{
				j++;													//incrementing if no record is found
			}
		}
	}
	file.close();														//closing "data.bin" file
	remove("data.bin");													//deleting "data.bin"
	f.close();															//closing temporary file
	fstream file2("data.bin", ios::out | ios::binary);					//creating new "data.bin" file
	f.open("temp.bin", ios::in | ios::binary);							//opening temporary file in read mode
	if (f.is_open())													//checking whether temporary file is opened or not
	{
		f.seekg(0, ios::beg);											//moving the file pointer to the beginning
		while (!f.eof())												//loop for checking end of temporary file
		{
			f.read((char*)&p, sizeof(phone));							//reading data from temporary file
			if (f.gcount() > 0)											//checking whether bytes read are greater than zero or not
			{
				file2.write((const char*)&p, sizeof(phone));			//writing data to new "data.bin" file
				li.push_front(p);										//storing new data in the list which does not contains deleted record
			}
		}
	}
	file2.close();														//closing new "data.bin" file
	f.close();															//closing temporary file
	remove("temp.bin");													//deleting temporary file
	if (j)
	{
		cout << "Record Deleted successfully!\n";
	}
	else
	{
		cout << "No record found to be deleted!\n";
	}
}