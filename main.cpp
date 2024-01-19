#define CROW_MAIN
//lab 10

#include "crow_all.h"
#include <iostream>
#include "string.h" 
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
using namespace crow;



int main()
{
	crow::SimpleApp app;

	CROW_ROUTE(app, "/") //to get the index.html
		([](const crow::request& req, crow::response& res) {
		
			});


		app.port(23500).multithreaded().run();
	return 1;
}