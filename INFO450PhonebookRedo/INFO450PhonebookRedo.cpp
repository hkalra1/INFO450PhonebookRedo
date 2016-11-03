// INFO450PhonebookRedo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;

class phoneBook
{
	char fullname[25];
	char homeNumber[10];
	char mobileNumber[10];

public:
	phoneBook();
	void enterphoneBook(char fn[], char hp[], char mp[]);
	void display();
	friend class friendList;

};

int main()
{
    return 0;
}

phoneBook::phoneBook()
{
}
