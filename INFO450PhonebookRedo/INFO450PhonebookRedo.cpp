// INFO450PhonebookRedo.cpp : Defines the entry point for the console application.
//Harry Kalra

//could not get the duplicate check to work

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;

class phoneBook 
{
	char fullName[25]; //first name and last name
	char homeNumber[25]; //home phone number
	char mobileNumber[25];// mobile phone number

public:
	phoneBook();
	void enterphoneBook(char fn[], char hn[], char mn[]);
	void display();
	friend class numberList; //friend class

};

phoneBook::phoneBook()
{
	strcpy_s(fullName, "");
	strcpy_s(homeNumber, "");
	strcpy_s(mobileNumber, "");

}

void phoneBook::enterphoneBook(char fn[], char hn[], char mn[])
{
	strcpy_s(fullName, fn);
	strcpy_s(homeNumber, hn);
	strcpy_s(mobileNumber, mn);

}

void phoneBook::display()
{
	cout << "Name:" << fullName << endl;
	cout << "Home Phone Number:" << homeNumber << endl;
	cout << "Mobile Phone Number:" << mobileNumber << endl;
}

class numberList
{
	char filename[100];
	int entryCount;
	phoneBook **contacts;

public:
	numberList();
	~numberList();
	void setfilename(char f[]);
	int getCount();
	void addToList(phoneBook *p);
	void shownameList();
	int savenameList();
	void readnameList();
};

numberList::numberList()
{
	contacts = new phoneBook*[100];
	entryCount = 0;
}

numberList::~numberList()
{
	delete contacts;
}

void numberList::setfilename(char f[])
{
	strcpy_s(filename, f);
}

int numberList::getCount()
{
	return entryCount;
}

void numberList::addToList(phoneBook * p)
{
	contacts[entryCount] = p;
	entryCount++;
}

void numberList::shownameList()
{
	for (int i = 0; i < entryCount; i++)
	{
		cout << "Record:" << i + 1 << endl;
		contacts[i]->display();

		if ((i + 1) % 5 == 0)
		{
			char answer;
			cout << "Press any key to continue" << endl;
			cin >> answer;
			cin.ignore();
		}
	}
}

int numberList::savenameList()
{
	ofstream output(filename);
	if (!output)
	{
		cout << "Incorrect." << endl;
		return -1;
	}
		for (int i = 0; i < entryCount; i++)
		{
			output << contacts[i]->fullName << "|";
			output << contacts[i]->homeNumber << "|";
			output << contacts[i]->mobileNumber << endl;
	}
		output.close();
		return 0;
}

void numberList::readnameList()
{
	ifstream infile(filename);
	if (!infile)
	{
		return;
	}

	while (!infile.eof())
	{
		phoneBook *ptr;
		char fullName[25];
		char homeNumber[10];
		char mobileNumber[10];

		infile.getline(fullName, 25, '|');
		if (strlen(fullName))
		{
			infile.getline(homeNumber, 10, '|');
			infile.getline(mobileNumber, 10);
			ptr = new phoneBook();
			ptr->enterphoneBook(fullName, homeNumber, mobileNumber);
			addToList(ptr);
		}
	}
	infile.close();
}
int main()
{
	char answer = 'y';
	char fullName[25];
	char homeNumber[25];
	char mobileNumber[25];
	char filename[50];

	numberList *bList = new numberList();

	cout << "Please enter the filename." << endl;
	gets_s(filename);
	bList->setfilename(filename);

	bList->readnameList();
	if (bList->getCount() == 0 || bList->getCount() < 100)
	{
		cout << "Your Phonebook has no names." << endl;
	}
	else
	{
		cout << "There are" << bList->getCount() << "numbers in your PhoneBook" << endl;
	}
	cout << "Would you like to add a number? Please enter Y to add an entry. Press E to Exit" << endl;
	cin >> answer;

	while (answer == 'Y' || answer == 'y')
	{
		cin.ignore();
		cin.clear();
		
			cout << "Enter the Full Name" << endl;
			gets_s(fullName);
			cout << "Enter the Home Phone Number" << endl;
			gets_s(homeNumber);
			cout << "Enter the Mobile Number" << endl;
			gets_s(mobileNumber);

			phoneBook *myphoneBook = new phoneBook();
			myphoneBook->enterphoneBook(fullName, homeNumber, mobileNumber);
			bList->addToList(myphoneBook);
	
			cout << "Would you like to add a number? Please enter Y to add an entry. Press E to Exit" << endl;
			cin >> answer;
		}

	bList->shownameList();
	bList->savenameList();

	return 0;
}

