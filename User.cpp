#include "User.h"

User::User() {
	this->email = "N/A";
	this->firstName = "N/A";
	this->lastName = "N/A";
	this->password = "N/A";
}

User::User(string email, string firstName, string lastName, string password) {
	this->email = email; 
	this->firstName = firstName;
	this->lastName = lastName;
	this->password = password;
}

void User::setFirstName(string firstName) {
	this->firstName = firstName;
}

void User::setEmail(string email) {
	this->email = email;
}

void User::setLastName(string lastName) {
	this->lastName = lastName;
}

void User::setPassword(string password) {
	this->password = password;
}

string User::getEmail(){
	return this->email;
}

string User::getFirstName() {
	return this->firstName;
} 

string User::getLastName() {
	return this->lastName;
}

string User::getPassword() {
	return this->password;
}