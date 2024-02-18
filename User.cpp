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
	}
	else {
		cout << "Task " << taskName << " not found in vector" << endl;
	}
}

void User::editTaskInVector(string taskName, string newTaskName, string newDueDate, string newDescription) { 
	for (int i = 0; i < this->tasks.size(); i++) {
		if (this->tasks[i].getTaskName() == taskName) {
			this->tasks[i].setTaskName(newTaskName);         
			this->tasks[i].setDueDate(newDueDate);
			this->tasks[i].setDescription(newDescription);
		}
	}
}

void User::editTaskNameInVector(string taskName, string newTaskName) {
	for (int i = 0; i < this->tasks.size(); i++) {
		if (this->tasks[i].getTaskName() == taskName) {
			this->tasks[i].setTaskName(newTaskName);
		}
	}
}

void User::editTaskDueDateInVector(string taskName, string newTaskDueDate) {
	for (int i = 0; i < this->tasks.size(); i++) {
		if (this->tasks[i].getTaskName() == taskName) {
			this->tasks[i].setDueDate(newTaskDueDate);
		}
	}
}

void User::editTaskDescriptionInVector(string taskName, string newTaskDescription) {
	for (int i = 0; i < this->tasks.size(); i++) {
		if (this->tasks[i].getTaskName() == taskName) { 
			this->tasks[i].setDescription(newTaskDescription);
		}
	}
}

void User::sortTaskvectorByName() {
	vector <string> taskNames;
	vector <Task> newTaskVector;

	for (int i = 0; i < tasks.size(); i++) {
		taskNames.push_back(this->tasks[i].getTaskName()); 
	}
	 
	std::sort(taskNames.begin(), taskNames.end());    

	for (int i = 0; i < taskNames.size(); i++) {
		for (int k = 0; k < this->tasks.size(); k++) {
			if (this->tasks[k].getTaskName() == taskNames[i]) {
				Task temp;
				temp.setTaskName(taskNames[i]);
				temp.setUserEmail(this->tasks[k].getUserEmail());
				temp.setDueDate(this->tasks[k].getDueDate());
				temp.setDescription(this->tasks[k].getDescription()); 

				newTaskVector.push_back(temp);
			}
		}
	}

	this->tasks.clear();

	for (int j = 0; j < newTaskVector.size(); j++) {
		this->tasks.push_back(newTaskVector[j]); 
	}
}
void User::sortTaskvectorByDate() {
	vector <string> taskDueDates; 
	vector <Task> newTaskVector; 

	for (int i = 0; i < tasks.size(); i++) {
		taskDueDates.push_back(this->tasks[i].getDueDate()); 
	}

	std::sort(taskDueDates.begin(), taskDueDates.end(), compareDates); 

	for (int i = 0; i < taskDueDates.size(); i++) { 
		for (int k = 0; k < this->tasks.size(); k++) { 
			if (this->tasks[k].getDueDate() == taskDueDates[i]) { 
				Task temp;
				temp.setDueDate(taskDueDates[i]);
				temp.setUserEmail(this->tasks[k].getUserEmail());
				temp.setTaskName(this->tasks[k].getTaskName()); 
				temp.setDescription(this->tasks[k].getDescription()); 

				newTaskVector.push_back(temp); 
				break;
			}
		}
	}

	this->tasks.clear();

	for (int j = 0; j < newTaskVector.size(); j++) {
		this->tasks.push_back(newTaskVector[j]);
	}
}
