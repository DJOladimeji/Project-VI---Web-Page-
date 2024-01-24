#define CROW_MAIN

#include "crow_all.h"
#include <iostream>
#include "string.h" 
#include <string>
#include <fstream>
#include <sstream>
#include "DB.h"
using namespace std;
using namespace crow;



int main()
{
    //---------------------------------------------------------------------DB setup-----------------------------------------------------------------------------------

    char* err;

    //Creating User DB
    sqlite3* userdb;
    sqlite3_stmt* userstmt;
    sqlite3_open("UserDb.db", &userdb);
    int userrc = sqlite3_exec(userdb, "CREATE TABLE IF NOT EXISTS User(email varchar(1000), firstName varChar(100), lastname varchar(100), password varchar(1000));", NULL, NULL, &err);

    if (userrc != SQLITE_OK) {
        cout << "error creating user DB: " << err << endl;
    }

    //Dumming adding data into DB====================================================================================================
    string userQuery = "insert into User VALUES ('Dave.oladimeji@gmail.com', 'David', 'Oladimeji', 'password');";
    userrc = sqlite3_exec(userdb, userQuery.c_str(), NULL, NULL, &err);
    if (userrc != SQLITE_OK) {
        cout << "error Manually adding user to DB" << err << endl;
    }

    sqlite3_prepare_v2(userdb, "select email, firstName, lastName, password from User", -1, &userstmt, 0);
    deleteUserFromDB(err, userdb, userstmt, "Dave.oladimeji@gmail.com");
    //================================================================================================================================


    //Creating Task DB
    sqlite3* taskdb;
    sqlite3_stmt* taskstmt;
    sqlite3_open("TaskDb.db", &taskdb);
    int taskrc = sqlite3_exec(taskdb, "CREATE TABLE IF NOT EXISTS Task(userEmail varchar(100), taskName varchar(100), dueDate varchar(100), description varchar(100));", NULL, NULL, &err);

    if (taskrc != SQLITE_OK) {
        cout << "error creating task DB: " << err << endl;
    }

    //Dumming adding data into DB=======================================================================================================
    string taskQuery = "insert into Task VALUES ('Dave.oladimeji@gmail.com', 'Slap Gurjit', '22 January 2024', 'Slap Gurjit in the face');";
    taskrc = sqlite3_exec(taskdb, taskQuery.c_str(), NULL, NULL, &err);
    if (taskrc != SQLITE_OK) {
        cout << "error Manually adding task to DB" << err << endl;
    }

    sqlite3_prepare_v2(taskdb, "select userEmail, taskName, dueDate, description from Task", -1, &taskstmt, 0);

    string deleteQuery = "DELETE FROM Task WHERE UserEmail = 'Dave.oladimeji@gmail.com' AND TaskName = 'Slap Gurjit';";

    int rc = sqlite3_exec(taskdb, deleteQuery.c_str(), NULL, NULL, &err);

    if (rc != SQLITE_OK) {
        cout << "delete error from Task DB: " << err << endl;
    }
    else {
        cout << "Task has been deleted from DB" << endl;
    }
    //=====================================================================================================================================

    cout << endl;
    cout << "================================================" << endl;
    cout << "Welcome to the TaskElite Server" << endl;
    cout << "================================================" << endl;
    cout << endl; 




	crow::SimpleApp app;

	CROW_ROUTE(app, "/") //to get the index.html
		([](const crow::request& req, crow::response& res) {
		
			});


		app.port(23500).multithreaded().run();
	return 1;
}