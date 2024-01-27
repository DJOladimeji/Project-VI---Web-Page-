#pragma once
#include <iostream>
#include <string>
#include "sqlite/sqlite3.h"
#include "DB.h"
#include "User.h"
#include"Task.h"
#include <iomanip>
#include <sstream>

using namespace std;

void addUserToDB(char* err, sqlite3* db, sqlite3_stmt* stmt, User user);
void addTaskToDB(char* err, sqlite3* db, sqlite3_stmt* stmt, Task task);  
User queryDBForAllTask(char* err, sqlite3* db, sqlite3_stmt* stmt, User user);
Task queryDBForSpecificTask(char* err, sqlite3* db, sqlite3_stmt* stmt, string task, User user);
bool queryUserLogin(char* err, sqlite3* db, sqlite3_stmt* stmt, User* user);
bool queryUserEmail(char* err, sqlite3* db, sqlite3_stmt* stmt, string enterdEmail); 
void deleteTaskFromDB(char* err, sqlite3* db, sqlite3_stmt* stmt, string task, User user); 
void deleteUserFromDB(char* err, sqlite3* db, sqlite3_stmt* stmt, string user);  
void editTask(char* err, sqlite3* db, sqlite3_stmt* stmt, User user, Task task, string newTaskName, string newDueDate, string newDescription);
void editTaskNameInDB(char* err, sqlite3* db, sqlite3_stmt* stmt, User user, string task, string newTaskName);
void editDuedateInDB(char* err, sqlite3* db, sqlite3_stmt* stmt, User user, string task, string newDueDate);
void editDescriptionInDB(char* err, sqlite3* db, sqlite3_stmt* stmt, User user, string task, string newDescription); 
std::string urlDecode(const std::string& input); 