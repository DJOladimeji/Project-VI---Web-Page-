#define CROW_MAIN

#include "crow_all.h"
#include "sqlite/sqlite3.h"
#include <iostream>
#include "string.h" 
#include <string>
#include <fstream>
#include <sstream>
#include "DB.h"
#include <vector>
#include <iomanip>
using namespace std;
using namespace crow;

User user; 
Task forIndividualTask; 
char* err; 
sqlite3* userdb; 
sqlite3_stmt* userstmt; 
sqlite3* taskdb; 
sqlite3_stmt* taskstmt; 
bool userLoggedIn = false; 
int main()
{
    //---------------------------------------------------------------------DB setup-----------------------------------------------------------------------------------


    //Creating User DB
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

	CROW_ROUTE(app, "/") //to get the home.html
		([](const crow::request& req, crow::response& res) {
            ifstream in("../public/home.html", ifstream::in);
            if (in) {
                ostringstream contents;
                contents << in.rdbuf();
                in.close();
                res.write(contents.str());
            }
            else {
                res.write("Not Found");
            }
            res.end();
		});

    /* CROW_ROUTE(app, "/<string>") //to get the home.html
        ([](const crow::request& req, crow::response& res, string filename) {
            if (filename == "SignUpPage.html")
            {
                string path = "../public/SignUpPage.html";

                ifstream in(path, ifstream::in);
                if (in) {
                    ostringstream contents;
                    contents << in.rdbuf();
                    in.close();
                    res.write(contents.str());
                }
                else {
                    res.write("Not Found");
                }
                res.end();
            }
        }); */ 


	CROW_ROUTE(app, "/<string>").methods(HTTPMethod::Get, HTTPMethod::Post, HTTPMethod::Patch, HTTPMethod::Delete, HTTPMethod::Put, HTTPMethod::Options)
		([](const crow::request& req, crow::response& res, string filename)
			{
				if (filename == "submit") {
					std::string submittedEmail = req.url_params.get("email");

                    bool checkingEmail = queryUserEmail(err, userdb, userstmt, submittedEmail);  

					if (checkingEmail == true) { 
						string path = "../public/SignInPage.html";

						ifstream in(path, ifstream::in);
						if (in) {
							ostringstream contents;
							contents << in.rdbuf();
							in.close();
							res.write(contents.str());
						}
						else {
							res.write("Not Found");
						}
						res.end(); 
					}
					else { 
					    // Redirect to the signup page
					    string path = "../public/SignUpPage.html";

					    ifstream in(path, ifstream::in);
					    if (in) {
						    ostringstream contents;
						    contents << in.rdbuf(); 
						    in.close();
						    res.write(contents.str());
					    }
					    else {
						    res.write("Not Found");
					    }
					    res.end();
					}
				}
				else if (filename == "SignUpPage.html") { 
				    string path = "../public/SignUpPage.html";

				    ifstream in(path, ifstream::in);
				    if (in) {
					    ostringstream contents;
					    contents << in.rdbuf();
					    in.close();
					    res.write(contents.str());
				    }
				    else {
					    res.write("Not Found");
				    }
				    res.end(); 
				} 
                else if (filename == "AddTaskPage") {
                    string path = "../public/Add_Task_Page.html";

                    ifstream in(path, ifstream::in);
                    if (in) {
                        ostringstream contents;
                        contents << in.rdbuf();
                        in.close();
                        res.write(contents.str());
                    }
                    else {
                        res.write("Not Found");
                    }
                    res.end(); 
                }
                else if (filename == "login") {
                    cout << "Entered route" << endl; 
                    
                    std::string passedEmail = req.url_params.get("email"); 
                    std::string passedPassword = req.url_params.get("password"); 
                    user.setEmail(passedEmail); 
                    user.setPassword(passedPassword); 

                    bool userFound = queryUserLogin(err, userdb, userstmt, &user); 

                    if (userFound)
                    {

                        if (userLoggedIn == false) {
                           user = queryDBForAllTask( err, taskdb, taskstmt, user); 
                        }
                        if (userLoggedIn == false) {
                            userLoggedIn = true; 
                        }

                        string path = "../public/taskspage.html";

                        ifstream in(path, ifstream::in);
                        if (in) {
                            ostringstream contents;
                            contents << in.rdbuf();
                            in.close();
                            res.write(contents.str());
                        }
                        else {
                            res.write("Not Found");
                        }
                        res.end(); 
                    }
                    else
                    {
                        string path = "../public/SignInPage.html"; 

                        ifstream in(path, ifstream::in);
                        if (in) {
                            ostringstream contents;
                            contents << in.rdbuf();
                            in.close();
                            res.write(contents.str());
                        }
                        else {
                            res.write("Not Found");
                        }
                        res.end();
                    }
                }
                else if (filename == "addtask") {
                    cout << "Entered add task route" << endl;


                    string post = "POST";
                    string method = method_name(req.method);
                    int resultPost = post.compare(method);

                    if (resultPost == 0) {

                        cout << "Entered check post" << endl; 

                        std::string taskName = req.url_params.get("taskName"); 
                        std::string taskDueDate = req.url_params.get("dueDate");  
                        std::string taskDescription = req.url_params.get("taskDescription"); 

                        /*auto json = crow::json::load(req.body);

                        if (!json) {
                            res.code = 400; // Bad Request
                            res.write("Error parsing JSON in the request body");
                            res.end();
                            return;
                        }

                        std::string taskName = json["taskName"].s();
                        std::string taskDueDate = json["dueDate"].s(); 
                        std::string taskDescription = json["taskDescription"].s();*/
                         


                        Task task; 
                        task.setUserEmail(user.getEmail());
                        task.setTaskName(taskName);  
                        task.setDueDate(taskDueDate);      
                        task.setDescription(taskDescription);

                        addTaskToDB(err, taskdb, taskstmt, task); 
                        user.addToTasksVector(task); 

                        string path = "../public/taskspage.html"; 

                        ifstream in(path, ifstream::in); 
                        if (in) {
                            ostringstream contents;
                            contents << in.rdbuf();
                            in.close();
                            res.write(contents.str());
                        }
                        else {
                            res.write("Not Found"); 
                        }
                        res.end(); 
                    } 
                }
                else if (filename == "Individual_Task_Page") {
                    cout << "Entered route" << endl;

                    std::string taskName = req.url_params.get("taskName"); 

                    forIndividualTask = queryDBForSpecificTask(err, taskdb, taskstmt, taskName, user); 

                    string path = "../public/Individual_Task_Page.html"; 

                    ifstream in(path, ifstream::in);
                    if (in) {
                        ostringstream contents; 
                        contents << in.rdbuf(); 
                        in.close(); 
                        res.write(contents.str()); 
                    }
                    else {
                        res.write("Not Found"); 
                    }
                    res.end(); 
                }
                else if (filename == "register") {
                    std::string firstName = req.url_params.get("firstName");
                    std::string lastName = req.url_params.get("lastName");
                    std::string passedEmail2 = req.url_params.get("email"); 
                    std::string passedPassword2 = req.url_params.get("password"); 

                    user.setEmail(passedEmail2); 
                    user.setFirstName(firstName); 
                    user.setLastName(lastName); 
                    user.setPassword(passedPassword2); 
                    addUserToDB(err, userdb, userstmt, user); 

                    string path = "../public/taskspage.html";

                    ifstream in(path, ifstream::in);
                    if (in) {
                        ostringstream contents;
                        contents << in.rdbuf();
                        in.close();
                        res.write(contents.str()); 
                    }
                    else {
                        res.write("Not Found");
                    }
                    res.end();
                }
                else if (filename == "editTaskName") {
                    string path = "../public/editTaskNamePage.html"; 

                    ifstream in(path, ifstream::in);
                    if (in) {
                        ostringstream contents;
                        contents << in.rdbuf();
                        in.close();
                        res.write(contents.str());
                    }
                    else {
                        res.write("Not Found");
                    }
                    res.end(); 
                }
                else if (filename == "editTaskDueDate") {
                    string path = "../public/editTaskDueDatePage.html";

                    ifstream in(path, ifstream::in);
                    if (in) {
                        ostringstream contents;
                        contents << in.rdbuf();
                        in.close();
                        res.write(contents.str());
                    }
                    else {
                        res.write("Not Found");
                    }
                    res.end();
                } 
                else if (filename == "editTaskDescription") {
                    string path = "../public/editTaskDescriptionPage.html";

                    ifstream in(path, ifstream::in);
                    if (in) {
                        ostringstream contents;
                        contents << in.rdbuf();
                        in.close();
                        res.write(contents.str());
                    }
                    else {
                        res.write("Not Found");
                    }
                    res.end(); 
                }
                else if (filename == "editAllTask") {
                    string path = "../public/editAllTaskPage.html"; 

                    ifstream in(path, ifstream::in);
                    if (in) {
                        ostringstream contents;
                        contents << in.rdbuf();
                        in.close();
                        res.write(contents.str());
                    }
                    else {
                        res.write("Not Found");
                    }
                    res.end();
                    }
                else if (filename == "taskspage") {
                    string path = "../public/taskspage.html";

                    ifstream in(path, ifstream::in);
                    if (in) {
                        ostringstream contents;
                        contents << in.rdbuf();
                        in.close();
                        res.write(contents.str());
                    }
                    else {
                        res.write("Not Found");
                    }
                    res.end();
                } 
                else if (filename == "newTaskName") {
                    cout << "Entered edit task name route" << endl; 

                    string patch = "PATCH";
                    string method = method_name(req.method); 
                    int resultPost = patch.compare(method); 

                    if (resultPost == 0) {
                        cout << "Entered check patch" << endl;

                        auto json = crow::json::load(req.body); 
                        cout << json << endl; 
                        if (!json) {
                            res.code = 400; // Bad Request
                            res.write("Error parsing JSON in the request body");
                            cout << "Error parsing JSON" << endl; 
                            res.end();
                            return;
                        }
                        else{
                            cout << "JSON is not empty" << endl; 
                            std::string newTaskName = json["newTaskName"].s(); 

                            cout << "New Task Name: " << newTaskName << endl; 

                            editTaskNameInDB(err, taskdb, taskstmt, user, forIndividualTask.getTaskName(), newTaskName); 

                            cout << "Task name should have been edited" << endl;
                        }

                        //const_cast<crow::request&>(req).method = crow::HTTPMethod::GET; 
                        //cout << method_name(req.method) << endl; 
                        //res.redirect("/taskspage"); 
                        //res.end(); 
                    }
                    else if (resultPost != 0) {
                        string path = "../public/taskspage.html";

                        ifstream in(path, ifstream::in);
                        if (in) {
                            ostringstream contents;
                            contents << in.rdbuf();
                            in.close(); 
                            res.write(contents.str());  
                        } 
                        else { 
                            res.write("Not Found"); 
                        }
                        res.end(); 
                    }
                }
                else if (filename == "newTaskDueDate") {
                    cout << "Entered edit task due date route" << endl;

                    string patch = "PATCH";
                    string method = method_name(req.method);
                    int resultPost = patch.compare(method);

                    if (resultPost == 0) {
                        cout << "Entered check patch 2" << endl;

                        auto json = crow::json::load(req.body);
                        cout << json << endl;
                        if (!json) {
                            res.code = 400; // Bad Request
                            res.write("Error parsing JSON in the request body");
                            cout << "Error parsing JSON" << endl;
                            res.end();
                            return;
                        }
                        else {
                            cout << "JSON is not empty" << endl;
                            std::string newTaskDueDate = json["newTaskDueDate"].s(); 

                            cout << "New Task Due Date: " << newTaskDueDate << endl;

                            editDuedateInDB(err, taskdb, taskstmt, user, forIndividualTask.getTaskName(), newTaskDueDate); 

                            cout << "Task due date should have been edited" << endl;
                        }

                        //const_cast<crow::request&>(req).method = crow::HTTPMethod::GET; 
                        //cout << method_name(req.method) << endl; 
                        //res.redirect("/taskspage"); 
                        //res.end(); 
                    }
                    else if (resultPost != 0) {
                        string path = "../public/taskspage.html";

                        ifstream in(path, ifstream::in);
                        if (in) {
                            ostringstream contents;
                            contents << in.rdbuf();
                            in.close();
                            res.write(contents.str());
                        }
                        else {
                            res.write("Not Found");
                        }
                        res.end();
                    }
                }
                else if (filename == "newTaskDescription") {
                    cout << "Entered edit task description route" << endl;

                    string patch = "PATCH";
                    string method = method_name(req.method);
                    int resultPost = patch.compare(method);

                    if (resultPost == 0) {
                        cout << "Entered check patch 3" << endl;

                        auto json = crow::json::load(req.body);
                        cout << json << endl;
                        if (!json) {
                            res.code = 400; // Bad Request
                            res.write("Error parsing JSON in the request body");
                            cout << "Error parsing JSON" << endl;
                            res.end();
                            return;
                        }
                        else {
                            cout << "JSON is not empty" << endl; 
                            std::string newTaskDescription = json["newTaskDescription"].s(); 

                            cout << "New Task Description: " << newTaskDescription << endl;

                            editDescriptionInDB(err, taskdb, taskstmt, user, forIndividualTask.getTaskName(), newTaskDescription); 

                            cout << "Task description should have been edited" << endl;
                        }

                        //const_cast<crow::request&>(req).method = crow::HTTPMethod::GET; 
                        //cout << method_name(req.method) << endl; 
                        //res.redirect("/taskspage"); 
                        //res.end(); 
                    }
                    else if (resultPost != 0) {
                        string path = "../public/taskspage.html";

                        ifstream in(path, ifstream::in);
                        if (in) {
                            ostringstream contents;
                            contents << in.rdbuf();
                            in.close();
                            res.write(contents.str());
                        }
                        else {
                            res.write("Not Found");
                        }
                        res.end();
                    }
                }
                else if (filename == "deleteTask") {
                    cout << "Entered delete task route" << endl; 

                    std::string deleteVerb = "DELETE";
                    std::string method = method_name(req.method); 
                    int resultDelete = deleteVerb.compare(method); 

                    if (resultDelete == 0) {
                        cout << "Entered check delete" << endl;

                        auto json = crow::json::load(req.body);
                        cout << json << endl;
                        if (!json) {
                            res.code = 400; // Bad Request
                            res.write("Error parsing JSON in the request body");
                            cout << "Error parsing JSON" << endl;
                            res.end();
                            return;
                        }
                        else {
                            cout << "JSON is not empty" << endl;
                            std::string taskName = json["taskName"].s(); 

                            cout << "Task name: " << taskName << endl; 

                            deleteTaskFromDB(err, taskdb, taskstmt, taskName, user); 
                            user = queryDBForAllTask(err, taskdb, taskstmt, user); 

                            cout << "Task should have been deleted" << endl; 
                        } 
                    }
                    else if (resultDelete != 0) { 
                        string path = "../public/taskspage.html";

                        ifstream in(path, ifstream::in);
                        if (in) {
                            ostringstream contents;
                            contents << in.rdbuf();
                            in.close();
                            res.write(contents.str());
                        }
                        else {
                            res.write("Not Found");
                        }
                        res.end(); 
                    }
                }
                else if (filename == "editTaskInformation") {
                    cout << "Entered edit task info route" << endl;

                    std::string put = "PUT";
                    std::string method = method_name(req.method);
                    int resultPut = put.compare(method); 

                    if (resultPut == 0) { 
                        cout << "Entered check put" << endl;

                        auto json = crow::json::load(req.body);
                        cout << json << endl;
                        if (!json) {
                            res.code = 400; // Bad Request
                            res.write("Error parsing JSON in the request body");
                            cout << "Error parsing JSON" << endl;
                            res.end();
                            return;
                        }
                        else {
                            cout << "JSON is not empty" << endl;
                            std::string newTaskName = json["newTaskName"].s(); 
                            std::string newTaskDueDate = json["newTaskDueDate"].s(); 
                            std::string newTaskDescription = json["newTaskDescription"].s(); 

                            cout << "New task name: " << newTaskName << endl; 
                            cout << "New task due date: " << newTaskDueDate << endl; 
                            cout << "New task description: " << newTaskDescription << endl; 

                            editTask(err, taskdb, taskstmt, user, forIndividualTask, newTaskName, newTaskDueDate, newTaskDescription); 

                            cout << "Task information should have been edited" << endl; 
                        } 
                    }
                    else if (resultPut != 0) { 
                        string path = "../public/taskspage.html";

                        ifstream in(path, ifstream::in);
                        if (in) {
                            ostringstream contents;
                            contents << in.rdbuf();
                            in.close();
                            res.write(contents.str());
                        }
                        else {
                            res.write("Not Found");
                        }
                        res.end();
                    }
                }

                else if (filename == "loadTaskPage") {

                    //std::string newTaskName = req.url_params.get("newTaskName");

                    //editTaskNameInDB(err, taskdb, taskstmt, user, forIndividualTask.getTaskName(), newTaskName);

                    string path = "../public/taskspage.html";

                    ifstream in(path, ifstream::in);
                    if (in) {
                        ostringstream contents;
                        contents << in.rdbuf();
                        in.close();
                        res.write(contents.str());
                    }
                    else {
                        res.write("Not Found");
                    }
                    res.end();
                }

                else if (filename == "sortByName") {  
                    cout << "Went into sort by Name route" << endl;

                    user.sortTaskvectorByName(); 

                    for (int i = 0; i < user.tasks.size(); i++) {
                        cout << "taskName: " << user.tasks[i].getTaskName() << endl;
                    }
                    res.end();
                } 

                else if (filename == "sortByDate") {

                    user.sortTaskvectorByDate();

                    for (int i = 0; i < user.tasks.size(); i++) {
                        cout << "Due date: " << user.tasks[i].getDueDate() << endl;
                    }

                    string path = "../public/taskspage.html";

                    ifstream in(path, ifstream::in);
                    if (in) {
                        ostringstream contents;
                        contents << in.rdbuf();
                        in.close();
                        res.write(contents.str());
                    }
                    else {
                        res.write("Not Found");
                    }
                    res.end();
                }
		}); 

    app.route_dynamic("/login/1").methods("GET"_method)
        ([]() {
        cout << "NEW ROUTE" << endl; 

        crow::json::wvalue jsonData; 

        //user = queryDBForAllTask(err, taskdb, taskstmt, user);
        string taskName, taskDescription, taskDueDate; 
        vector <string> vectTaskName; 
        vector <string> vectTaskDescription;
        vector <string> vectTaskDueDate;

        for (int i = 0; i < user.tasks.size(); i++) 
        {
            taskName = user.tasks[i].getTaskName(); 
            taskDescription = user.tasks[i].getDescription(); 
            taskDueDate = user.tasks[i].getDueDate();

            cout << "Task Name in login/1 route: " << user.tasks[i].getTaskName() << endl; 
            cout << "Task Due date in login/1 route: " << user.tasks[i].getDueDate() << endl;

            vectTaskName.push_back(taskName); 
            vectTaskDescription.push_back(taskDescription); 
            vectTaskDueDate.push_back(taskDueDate); 
        } 

        //Have the sign in page call the /login and have /login open the tasksPage.html which will fetch the /login/1 route (JSON) 
        // Simulated JSON data

        jsonData["taskName"] = vectTaskName;  
        jsonData["taskDescription"] = vectTaskDescription; 
        jsonData["taskDueDate"] = vectTaskDueDate;  

        std::cout << "Vector size before clearing: " << vectTaskName.size() << std::endl;

        vectTaskName.clear(); 
        vectTaskDescription.clear(); 
        vectTaskDueDate.clear(); 
        if (vectTaskName.empty()) {
            cout << "vect is empty" << endl; 
            std::cout << "Vector size after clearing: " << vectTaskName.size() << std::endl; 
        }
        else
        {
            cout << "vect is not empty" << endl; 
        }

        return crow::response(jsonData.dump());  
        }); 

    CROW_ROUTE(app, "/<string>/<string>/<string>/<string>").methods(HTTPMethod::Post) 
        ([](const crow::request& req, crow::response& res, string filename, string taskName, string dueDate, string taskDescription)
        {
            string post = "POST"; 
            string method = method_name(req.method); 
            int resultPost = post.compare(method); 

            if (resultPost == 0) {
                cout << "Adding a task route" << endl;

                std::string decodedTaskName = urlDecode(taskName); 
                std::string decodedTaskDescription = urlDecode(taskDescription); 

                Task task;
                task.setUserEmail(user.getEmail());
                task.setTaskName(decodedTaskName);
                task.setDueDate(dueDate); 
                task.setDescription(decodedTaskDescription); 

                addTaskToDB(err, taskdb, taskstmt, task);
                user.addToTasksVector(task);

                string path = "../public/taskspage.html";

                ifstream in(path, ifstream::in);
                if (in) {
                    ostringstream contents;
                    contents << in.rdbuf();
                    in.close();
                    res.write(contents.str()); 
                }
                else {
                    res.write("Not Found");
                }
                res.end(); 
            }
        });

    CROW_ROUTE(app, "/Individual_Task_Page/<string>") 
        ([](const crow::request& req, crow::response& res, string taskName) 
            {
                forIndividualTask = queryDBForSpecificTask(err, taskdb, taskstmt, taskName, user); 

                string path = "../public/Individual_Task_Page.html"; 

                ifstream in(path, ifstream::in);
                if (in) {
                    ostringstream contents; 
                    contents << in.rdbuf();   
                    in.close(); 
                    res.write(contents.str()); 
                }
                else {
                    res.write("Not Found"); 
                }
                res.end();
        }); 

    app.route_dynamic("/IndividualTask/1").methods("GET"_method)
        ([]() {

        crow::json::wvalue jsonData;

        jsonData["taskName"] = forIndividualTask.getTaskName();
        jsonData["taskDescription"] = forIndividualTask.getDescription();
        jsonData["taskDueDate"] = forIndividualTask.getDueDate();

        return crow::response(jsonData.dump());
            });

    CROW_ROUTE(app, "/deleteTask/<string>").methods(HTTPMethod::Delete) 
        ([](const crow::request& req, crow::response& res, string taskName) 
            {
                cout << "Delete route" << endl; 

                deleteTaskFromDB(err, taskdb, taskstmt, taskName, user); 

                string path = "../public/taskpage.html";

                ifstream in(path, ifstream::in);
                if (in) {
                    ostringstream contents;
                    contents << in.rdbuf();
                    in.close();
                    res.write(contents.str());
                }
                else {
                    res.write("Not Found");
                }
                res.end();
        });

    CROW_ROUTE(app, "/styles/<string>")											//style.css route 
        ([](const crow::request& req, crow::response& res, string filename) 
            {
                string TempPath = "../public/styles/";
                string path = TempPath + filename;

                ifstream in(path, ifstream::in);
                if (in) {
                    ostringstream contents;
                    contents << in.rdbuf();
                    in.close();
                    res.write(contents.str());
                }
                else {
                    res.write("Not Found");
                }
                res.end();
        });

    CROW_ROUTE(app, "/images/<string>")											//images route (all images) 
        ([](const crow::request& req, crow::response& res, string filename)
            {
                string TempPath = "../public/images/";
                string path = TempPath + filename;

                ifstream in(path, ifstream::in);
                if (in) {
                    ostringstream contents;
                    contents << in.rdbuf();
                    in.close();
                    res.write(contents.str());
                }
                else {
                    res.write("Not Found");
                }
                res.end();
        });

    CROW_ROUTE(app, "/scripts/<string>")											//scripts route (all scripts) 
        ([](const crow::request& req, crow::response& res, string filename) 
            {
                string TempPath = "../public/scripts/"; 
                string path = TempPath + filename; 

                ifstream in(path, ifstream::in); 
                if (in) {
                    ostringstream contents;
                    contents << in.rdbuf();
                    in.close();
                    res.write(contents.str());
                }
                else {
                    res.write("Not Found");
                }
                res.end();
        });


		app.port(23500).multithreaded().run();
	return 1;
} 