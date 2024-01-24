#pragma once
#include <iostream>
using namespace std;

class User {
	string email;
	string firstName;
	string lastName;
	string password;


public:
	User();
	User(string email, string firstName, string lastName, string password);

	void setEmail(string email);
	void setFirstName(string firstName);
	void setLastName(string lastName);
	void setPassword(string password);
	string getEmail();
	string getFirstName();
	string getLastName();
	string getPassword();
};