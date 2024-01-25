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
using namespace std;
using namespace crow;

User user; 
char* err; 
sqlite3* userdb; 
sqlite3_stmt* userstmt; 
sqlite3* taskdb; 
sqlite3_stmt* taskstmt; 

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

	std::string correctEmail = "user@example.com"; // Replace with your correct email 

	CROW_ROUTE(app, "/<string>").methods(HTTPMethod::Get, HTTPMethod::Post)
		([&correctEmail](const crow::request& req, crow::response& res, string filename)
			{
				if (filename == "submit") {
					std::string submittedEmail = req.url_params.get("email");
					//res.write("EMAIL"); 
					//res.end(); 
					if (submittedEmail == correctEmail) { 
						//-------------- 
							/* ofstream fout;
							fout.open("cart.txt", ios::app);
							if (fout.is_open()) {
								fout << "CORRECT: " << submittedEmail << endl; 

								res.code = OK;
								fout.close();
							}
							else
							{
								res.code = INVALID;
								res.set_header("Content-Type", "text/plain");
								res.write("Could not open file");
							}

							res.end(); */ 

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

							
							/* res.redirect("/SignInPage");
							res.end(); */ 
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

					//return crow::response(301).set_header("Location", "/Signup.html");

					//--------------
					/* res.redirect("/SignUpPage.html");
					res.end(); */ 
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
				//string username = "Gurjit"; 

				//crow::mustache::context ctx; 
				//ctx["username"] = username;

				// Respond with a template that embeds the username in the HTML
				//return crow::mustache::load("Login.html").render(ctx); 
				//return crow::response(crow::mustache::load("Login.html", ctx)); 

				//return crow::mustache::load("Login.html").render({{"username", username}}); 
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
		}); 

    app.route_dynamic("/login/1").methods("GET"_method)
        ([]() {
        cout << "NEW ROUTE" << endl; 

        crow::json::wvalue jsonData; 

        user = queryDBForAllTask(err, taskdb, taskstmt, user);
        string taskName, taskDescription, taskDueDate; 
        vector <string> vectTaskName; 
        vector <string> vectTaskDescription;
        vector <string> vectTaskDueDate;

        for (int i = 0; i < user.tasks.size(); i++) 
        {
            taskName = user.tasks[i].getTaskName(); 
            taskDescription = user.tasks[i].getDescription(); 
            taskDueDate = user.tasks[i].getDueDate(); 

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
                cout << "DAVID" << endl;

                /* std::string taskName = req.url_params.get("taskName");
                std::string taskDueDate = req.url_params.get("dueDate");
                std::string taskDescription = req.url_params.get("taskDescription"); */ 

                Task task;
                task.setUserEmail(user.getEmail());
                task.setTaskName(taskName);
                task.setDueDate(dueDate); 
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


		app.port(23500).multithreaded().run();
	return 1;
}