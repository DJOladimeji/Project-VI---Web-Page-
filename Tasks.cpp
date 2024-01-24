#include "Task.h"

Task::Task() {
	this->userEmail = "N/A";
	this->taskName = "N/A";
	this->dueDate = "N/A";
	this->description = "N/A";
}
Task::Task(string userEmail, string taskName, string dueDate, string description) {
	this->userEmail = userEmail;
	this->taskName = taskName;
	this->dueDate = dueDate;
	this->description = description;
}

void Task::setUserEmail(string userEmail) {
	this->userEmail = userEmail;
}

void Task::setTaskName(string taskName) {
	this->taskName = taskName;
}

void Task::setDueDate(string dueDate) {
	this->dueDate = dueDate;
}

void Task::setDescription(string description) {
	this->description = description;
}

string Task::getUserEmail() {
	return this->userEmail;
}

string Task::getTaskName() {
	return this->taskName;
}

string Task::getDueDate() {
	return this->dueDate;
}

string Task::getDescription() {
	return this->description; 
}