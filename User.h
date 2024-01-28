#pragma once
#include <iostream>
using namespace std;
#include "Task.h"
#include <vector>
#include <string>
#include <algorithm>

class User {
	string email;
	string firstName;
	string lastName;
	string password;

public:
	vector <Task> tasks; 
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
	void addToTasksVector(Task task);
	void removeFromTaskvector(string taskName);
	void editTaskInVector(string taskName, string newTasKName, string newDueDate, string newDescription);
	void editTaskNameInVector(string taskName, string newTaskName);
	void editTaskDueDateInVector(string taskName, string newTaskDueDate);
	void editTaskDescriptionInVector(string taskName, string newTaskDescription);  
	void sortTaskvectorByName(); 
	void sortTaskvectorByDate(); 


	static bool compareDates(const std::string& date1, const std::string& date2) {
		return date1 < date2;
	}
};