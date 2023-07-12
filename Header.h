#include <iostream>
#include <list>
#include <fstream>
#include <string>
using namespace std;

struct phone {				//structure for storing records
	int id, ram, rom;							//djfferent properties of mobile phone
	char maker[20], model[10];
	double screen, price;
	friend ostream& operator << (ostream&, const phone&);			//<< operator overloading
};

void display(const list<phone>&);									//function for displaying records
void open(fstream&, phone&, list<phone>&);							//function for opening file								
void operations(fstream&, phone&, list<phone>&);					//function for performing operations
void addphone(phone&,list<phone>&);									//function for adding record
void addwhileupdate(phone&);										//function for adding while updating
void searchphone(const phone&, const list<phone>&);					//function for searching phone
void searchbyid(const list<phone>&);								//function for searching phone by id
void searchbymaker(const list<phone>&);								//function for searching phone by maker
void searchbymodel(const list<phone>&);								//function for searching phone by model
void searchbyram(const list<phone>&);								//function for searching phone by ram
void searchbyrom(const list<phone>&);								//function for searching phone by rom
void searchbyscreen(const list<phone>&);							//function for searching phone by display size
void searchbyprice(const list<phone>&);								//function for searching phone by price
void updatephone(phone&, list<phone>&);								//function for updating phone record
void deletephone(phone&, list<phone>&);								//function for deleting phone record
