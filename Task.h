#pragma once
#include <iostream>
using namespace std; 

class Task {
	string userEmail;
	string taskName;
	string dueDate;
	string description;

public:
	Task();
	Task(string userEmail, string taskName, string dueDate, string description);

	void setUserEmail(string userEmail);
	void setTaskName(string taskName);
	void setDueDate(string dueDate);
	void setDescription(string description);
	string getUserEmail();
	string getTaskName();
	string getDueDate();
	string getDescription();
};