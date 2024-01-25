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

void User::addToTasksVector(Task task) {
	this->tasks.push_back(task);
}

void User::removeFromTaskvector(string taskName) {
	// Use find_if to search for the tasks with the specified taskName
	auto it = find_if(this->tasks.begin(), this->tasks.end(), [taskName](Task& task) {
		return task.getTaskName() == taskName; 
		});

	//check to is if the task was found 
	if (it != this->tasks.end()) {
		//use erase-remove idiom to delete the task
		this->tasks.erase(it); 
		std::cout << "Task " << taskName << " has been reased from vector" << endl;
	}
	else {
		cout << "Task " << taskName << " not found in vector" << endl;
	}
}

void User::editTaskInVector(string taskName, string newTasKName, string newDueDate, string newDescription) { 
	auto it = find_if(this->tasks.begin(), this->tasks.end(), [taskName](Task& task) {
		return task.getTaskName() == taskName;
		});

	//check if the task was found
	if (it != this->tasks.end()) {
		it->setTaskName(newTasKName);
		it->setTaskName(newDueDate);
		it->setDescription(newDescription); 

		cout << "Task " << taskName << " has bee editetd enterily in the vector" << endl;
	}
	else {
		cout << "Task " << taskName << " was not found in the vector" << endl;
	}
}

void User::editTaskNameInVector(string taskName, string newTaskName) {
	auto it = find_if(this->tasks.begin(), this->tasks.end(), [taskName](Task& task) {
		return task.getTaskName() == taskName;
		});

	//check if the task was found
	if (it != this->tasks.end()) {
		it->setTaskName(newTaskName);
		cout << "Task " << taskName << " Name, has not been editted to " << newTaskName << " in the vector" << endl;
	}
	else {
		cout << "Task " << taskName << " was not found in the vector" << endl;  
	}
}

void User::editTaskDueDateInVector(string taskName, string newTaskDueDate) {
	auto it = find_if(this->tasks.begin(), this->tasks.end(), [taskName](Task& task) {   
		return task.getTaskName() == taskName;  
		});

	//check if the task was found
	if (it != this->tasks.end()) { 
		it->setDueDate(newTaskDueDate);  
		cout << "Task " << taskName << " Due date, has not been editted to " << newTaskDueDate << " in the vector" << endl; 
	}
	else {
		cout << "Task " << taskName << " was not found in the vector" << endl; 
	}
}

void User::editTaskDescriptionInVector(string taskName, string newTaskDescription) {
	auto it = find_if(this->tasks.begin(), this->tasks.end(), [taskName](Task& task) { 
		return task.getTaskName() == taskName;
		});

	//check if the task was found
	if (it != this->tasks.end()) {
		it->setDescription(newTaskDescription); 
		cout << "Task " << taskName << " Description, has not been editted to " << newTaskDescription << " in the vector" << endl;  
	}
	else {
		cout << "Task " << taskName << " was not found in the vector" << endl; 
	}
}