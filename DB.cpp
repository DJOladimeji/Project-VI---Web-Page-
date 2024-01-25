#include "DB.h"
#include "cstring"

void addUserToDB(char* err, sqlite3* db, sqlite3_stmt* stmt, User user) {
    string query = "insert into User VALUES ('"+ user.getEmail() + "', '" + user.getFirstName() + "', '" + user.getLastName() + "', '" + user.getPassword() + "');";

    int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &err);

    if (rc != SQLITE_OK) {
        cout << "insert error to User DB: " << err << endl;
    }

    cout << "User has been added to DB" << endl;
}

void addTaskToDB(char* err, sqlite3* db, sqlite3_stmt* stmt, Task task) {
    string query = "insert into Task VALUES ('" + task.getUserEmail() + "', '" + task.getTaskName() + "', '" + task.getDueDate() + "', '" +task.getDescription() + "');";

    int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &err); 

    if (rc != SQLITE_OK) {
        cout << "insert error to Task DB: " << err << endl; 
    }

    cout << "Task has been added to DB" << endl;
}

User queryDBForAllTask(char* err, sqlite3* db, sqlite3_stmt* stmt, User user) {
    sqlite3_prepare_v2(db, "select userEmail, taskName, dueDate, description from Task", -1, &stmt, 0);
 
    const unsigned char* userEmail;
    const unsigned char* taskName; 
    const unsigned char* dueDate;
    const unsigned char* description;

    while (sqlite3_step(stmt) != SQLITE_DONE) { 
        userEmail = sqlite3_column_text(stmt, 0);
        taskName = sqlite3_column_text(stmt, 1);
        dueDate = sqlite3_column_text(stmt, 2);
        description = sqlite3_column_text(stmt, 3);

        int emaillen = strlen((char*)userEmail);
        std::string stringEmail(reinterpret_cast<const char*>(userEmail), emaillen);
        
        if (stringEmail == user.getEmail()) {

            int taskNamelen = strlen((char*)taskName);
            std::string stringTaskName(reinterpret_cast<const char*>(taskName), taskNamelen);

            int dueDatelen = strlen((char*)dueDate); 
            std::string stringDueDate(reinterpret_cast<const char*>(dueDate), dueDatelen);

            int descriptionlen = strlen((char*)description);
            std::string stringDescription(reinterpret_cast<const char*>(description), descriptionlen); 

            Task task(stringEmail, stringTaskName, stringDueDate, stringDescription);  

            bool isalreadythere = false;

            for (int i = 0; i < user.tasks.size(); i++) { 
                if (user.tasks[i].getTaskName() == stringTaskName) {
                    isalreadythere = true;
                }
            }

            if (isalreadythere == false) {
                user.addToTasksVector(task); 
            } 
        }
    }

    return user;  
} 

Task queryDBForSpecificTask(char* err, sqlite3* db, sqlite3_stmt* stmt, string task, User user) {
    sqlite3_prepare_v2(db, "select userEmail, taskName, dueDate, description from Task", -1, &stmt, 0);

    const unsigned char* userEmail;
    const unsigned char* taskName;
    const unsigned char* dueDate;
    const unsigned char* description;

    while (sqlite3_step(stmt) != SQLITE_DONE) {

        Task tasks;

        userEmail = sqlite3_column_text(stmt, 0);
        taskName = sqlite3_column_text(stmt, 1);
        dueDate = sqlite3_column_text(stmt, 2);
        description = sqlite3_column_text(stmt, 3);

        int taskNamelen = strlen((char*)taskName);
        int emaillen = strlen((char*)userEmail);

        std::string stringUserEmail(reinterpret_cast<const char*>(userEmail), emaillen);
        std::string stringTaskName(reinterpret_cast<const char*>(taskName), taskNamelen);

        if (stringUserEmail == user.getEmail() && stringTaskName == task) { 
            int taskNamelen = strlen((char*)taskName); 
            std::string stringTaskName(reinterpret_cast<const char*>(taskName), taskNamelen); 

            int dueDatelen = strlen((char*)dueDate); 
            std::string stringDueDate(reinterpret_cast<const char*>(dueDate), dueDatelen); 

            int descriptionlen = strlen((char*)description); 
            std::string stringDescription(reinterpret_cast<const char*>(description), descriptionlen); 

            tasks.setUserEmail(stringTaskName);
            tasks.setTaskName(stringTaskName); 
            tasks.setDueDate(stringDueDate);  
            tasks.setDescription(stringDescription);  

            return tasks; 
        }

    }
}

bool queryUserLogin(char* err, sqlite3* db, sqlite3_stmt* stmt, User* user) { 
    sqlite3_prepare_v2(db, "select email, firstName, lastName, password from User", -1, &stmt, 0);

    const unsigned char* email;
    const unsigned char* firstName;
    const unsigned char* lastName;
    const unsigned char* password;

    bool userfound = false;

    while (sqlite3_step(stmt) != SQLITE_DONE) {
        email = sqlite3_column_text(stmt, 0);
        firstName = sqlite3_column_text(stmt, 1);
        lastName = sqlite3_column_text(stmt, 2);
        password = sqlite3_column_text(stmt, 3);

        int emaillen = strlen((char*)email);
        int passwordlen = strlen((char*)password); 

        std::string stringEmail(reinterpret_cast<const char*>(email), emaillen);  
        std::string stringPassword(reinterpret_cast<const char*>(password), passwordlen);

        if (stringEmail == user->getEmail() && stringPassword == user->getPassword()) {
            std::string stringFirstName(reinterpret_cast<const char*>(firstName), sizeof(firstName));
            std::string StringLastName(reinterpret_cast<const char*>(lastName), sizeof(lastName));

            user->setFirstName(stringFirstName);
            user->setLastName(StringLastName); 
            
            cout << "User is in the Database" << endl;
            userfound = true;
            break;
        }
    }

    return userfound;
}

bool queryUserEmail(char* err, sqlite3* db, sqlite3_stmt* stmt, string enteredEmail) {
    sqlite3_prepare_v2(db, "select email, firstName, lastName, password from User", -1, &stmt, 0);

    const unsigned char* email;
    const unsigned char* firstName;
    const unsigned char* lastName;
    const unsigned char* password;

    bool userfound = false;

    while (sqlite3_step(stmt) != SQLITE_DONE) { 
        email = sqlite3_column_text(stmt, 0); 
        firstName = sqlite3_column_text(stmt, 1); 
        lastName = sqlite3_column_text(stmt, 2); 
        password = sqlite3_column_text(stmt, 3); 

        int emaillen = strlen((char*)email);

        std::string stringEmail(reinterpret_cast<const char*>(email), emaillen); 

        if (stringEmail == enteredEmail) {     
            cout << "User is in the Database" << endl; 
            userfound = true;
            break;
        }
    }

    return userfound;
}

void deleteTaskFromDB(char* err, sqlite3* db, sqlite3_stmt* stmt, string task, User user){
    string deleteQuery = "DELETE FROM Task WHERE UserEmail = '" + user.getEmail() + "' AND TaskName = '" + task + "';";

    int rc = sqlite3_exec(db, deleteQuery.c_str(), NULL, NULL, &err);

    if (rc != SQLITE_OK) {
        cout << "delete error from Task DB: " << err << endl;
    }
    else {
        cout << "Task has been deleted from DB" << endl;
    }

    user.removeFromTaskvector(task);
}

void deleteUserFromDB(char* err, sqlite3* db, sqlite3_stmt* stmt, string email) { 
    string deleteQuery = "DELETE FROM User WHERE email = '" + email + "';";

    int rc = sqlite3_exec(db, deleteQuery.c_str(), NULL, NULL, &err);

    if (rc != SQLITE_OK) {
        cout << "delete error from User DB: " << err << endl;
    }
    else {
        cout << "User has been deleted from DB" << endl;
    }
}

void editTask(char* err, sqlite3* db, sqlite3_stmt* stmt, User user, Task task, string newTaskName, string newDueDate, string newDescription) {
    sqlite3_prepare_v2(db, "select userEmail, taskName, dueDate, description from Task", -1, &stmt, 0);

    const unsigned char* userEmail;
    const unsigned char* taskName;
    const unsigned char* dueDate;
    const unsigned char* description;

    while (sqlite3_step(stmt) != SQLITE_DONE) {
        userEmail = sqlite3_column_text(stmt, 0);
        taskName = sqlite3_column_text(stmt, 1);
        dueDate = sqlite3_column_text(stmt, 2);
        description = sqlite3_column_text(stmt, 3);

        int emaillen = strlen(reinterpret_cast<const char*>(userEmail));
        std::string stringEmail(reinterpret_cast<const char*>(userEmail), emaillen);

        int taskNamelen = strlen(reinterpret_cast<const char*>(taskName));
        std::string stringTaskName(reinterpret_cast<const char*>(taskName), taskNamelen);

        if (stringEmail == user.getEmail() && stringTaskName == task.getTaskName()) {
            // Match found, update the task in the database
            std::string updateQuery = "UPDATE Task SET taskName = '"+newTaskName+"', dueDate = '"+newDueDate+"', description = '"+newDescription+"' WHERE taskName = '"+task.getTaskName()+ "'";
            sqlite3_stmt* updateStmt;

            int rc = sqlite3_prepare_v2(db, updateQuery.c_str(), -1, &updateStmt, 0); 
            if (rc != SQLITE_OK) { 
                std::cerr << "Error preparing update statement: " << sqlite3_errmsg(db) << std::endl;
                return;
            }

            // Execute the update statement
            rc = sqlite3_step(updateStmt); 
            if (rc != SQLITE_OK) { 
                std::cerr << "Error updating task: " << sqlite3_errmsg(db) << std::endl; 
            }
            else {
                std::cout << "Task updated successfully." << std::endl;
                user.editTaskInVector(task.getTaskName(), newTaskName, newDueDate, newDescription); 
            } 

            sqlite3_finalize(updateStmt); // Finalize the update statement
            return;
        }
    }

    std::cout << "Task not found." << std::endl;
}

void editTaskNameInDB(char* err, sqlite3* db, sqlite3_stmt* stmt, User user, string task, string newTaskName) {
    sqlite3_prepare_v2(db, "select userEmail, taskName, dueDate, description from Task", -1, &stmt, 0);

    const unsigned char* userEmail;
    const unsigned char* taskName; 
    const unsigned char* dueDate;
    const unsigned char* description;

    while (sqlite3_step(stmt) != SQLITE_DONE) {
        userEmail = sqlite3_column_text(stmt, 0);
        taskName = sqlite3_column_text(stmt, 1);
        dueDate = sqlite3_column_text(stmt, 2);
        description = sqlite3_column_text(stmt, 3);

        int emaillen = strlen(reinterpret_cast<const char*>(userEmail));
        std::string stringEmail(reinterpret_cast<const char*>(userEmail), emaillen);

        int taskNamelen = strlen(reinterpret_cast<const char*>(taskName));
        std::string stringTaskName(reinterpret_cast<const char*>(taskName), taskNamelen);

        if (stringEmail == user.getEmail() && stringTaskName == task) {
            // Match found, update the task in the database
            std::string updateQuery = "UPDATE Task SET taskName = '"+newTaskName+"' WHERE taskName = '"+task+"'";
            sqlite3_stmt* updateStmt;

            int rc = sqlite3_prepare_v2(db, updateQuery.c_str(), -1, &updateStmt, 0);
            if (rc != SQLITE_OK) {
                std::cerr << "Error preparing update statement: " << sqlite3_errmsg(db) << std::endl;
                return;
            }

            // Execute the update statement
            rc = sqlite3_step(updateStmt);
            if (rc != SQLITE_DONE) {
                std::cerr << "Error updating Task Name: " << sqlite3_errmsg(db) << std::endl;
            }
            else {
                std::cout << "Task Name updated successfully." << std::endl;

                user.editTaskNameInVector(task, newTaskName); 
            }

            sqlite3_finalize(updateStmt); // Finalize the update statement
            return;
        }
    }

    std::cout << "Task not found." << std::endl;
}

void editDuedateInDB(char* err, sqlite3* db, sqlite3_stmt* stmt, User user, string task, string newDueDate) {
    sqlite3_prepare_v2(db, "select userEmail, taskName, dueDate, description from Task", -1, &stmt, 0);

    const unsigned char* userEmail;
    const unsigned char* taskName;
    const unsigned char* dueDate;
    const unsigned char* description;

    while (sqlite3_step(stmt) != SQLITE_DONE) {
        userEmail = sqlite3_column_text(stmt, 0);
        taskName = sqlite3_column_text(stmt, 1);
        dueDate = sqlite3_column_text(stmt, 2);
        description = sqlite3_column_text(stmt, 3);

        int emaillen = strlen(reinterpret_cast<const char*>(userEmail));
        std::string stringEmail(reinterpret_cast<const char*>(userEmail), emaillen);

        int taskNamelen = strlen(reinterpret_cast<const char*>(taskName));
        std::string stringTaskName(reinterpret_cast<const char*>(taskName), taskNamelen);

        if (stringEmail == user.getEmail() && stringTaskName == task) {
            // Match found, update the task in the database
            std::string updateQuery = "UPDATE Task SET dueDate = '"+newDueDate+"' WHERE taskName = '"+task+"'";
            sqlite3_stmt* updateStmt;

            int rc = sqlite3_prepare_v2(db, updateQuery.c_str(), -1, &updateStmt, 0);
            if (rc != SQLITE_OK) {
                std::cerr << "Error preparing update statement: " << sqlite3_errmsg(db) << std::endl;
                return;
            }

            // Execute the update statement
            rc = sqlite3_step(updateStmt);
            if (rc != SQLITE_DONE) {
                std::cerr << "Error updating Due Date: " << sqlite3_errmsg(db) << std::endl;
            }
            else {
                std::cout << "Du eDate updated successfully." << std::endl;

                user.editTaskDueDateInVector(task, newDueDate); 
            }

            sqlite3_finalize(updateStmt); // Finalize the update statement
            return;
        }
    }

    std::cout << "Task not found." << std::endl;

}

void editDescriptionInDB(char* err, sqlite3* db, sqlite3_stmt* stmt, User user, string task, string newDescription) {
    sqlite3_prepare_v2(db, "select userEmail, taskName, dueDate, description from Task", -1, &stmt, 0);

    const unsigned char* userEmail;
    const unsigned char* taskName;
    const unsigned char* dueDate;
    const unsigned char* description;

    while (sqlite3_step(stmt) != SQLITE_DONE) {
        userEmail = sqlite3_column_text(stmt, 0);
        taskName = sqlite3_column_text(stmt, 1);
        dueDate = sqlite3_column_text(stmt, 2);
        description = sqlite3_column_text(stmt, 3);

        int emaillen = strlen(reinterpret_cast<const char*>(userEmail));
        std::string stringEmail(reinterpret_cast<const char*>(userEmail), emaillen);

        int taskNamelen = strlen(reinterpret_cast<const char*>(taskName));
        std::string stringTaskName(reinterpret_cast<const char*>(taskName), taskNamelen);

        if (stringEmail == user.getEmail() && stringTaskName == task) {
            // Match found, update the task in the database
            std::string updateQuery = "UPDATE Task SET description = '"+newDescription+"' WHERE taskName = '"+task+"'";
            sqlite3_stmt* updateStmt;

            int rc = sqlite3_prepare_v2(db, updateQuery.c_str(), -1, &updateStmt, 0);
            if (rc != SQLITE_OK) {
                std::cerr << "Error preparing update statement: " << sqlite3_errmsg(db) << std::endl;
                return;
            }


            // Execute the update statement
            rc = sqlite3_step(updateStmt);
            if (rc != SQLITE_DONE) {
                std::cerr << "Error updating task: " << sqlite3_errmsg(db) << std::endl;
            }
            else {
                std::cout << "Task updated successfully." << std::endl;

                user.editTaskDescriptionInVector(task, newDescription); 
            }

            sqlite3_finalize(updateStmt); // Finalize the update statement
            return;
        }
    }

    std::cout << "Task not found." << std::endl;
}