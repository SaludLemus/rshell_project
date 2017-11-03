#include "user.h"
#include <string>
#include <iostream>
using namespace std;

User::User() : cmd_controller(0) {}

User::~User() {
	if (cmd_controller) // ensure proper deallocation
      delete cmd_controller;
   cmd_controller = 0;
}

void User::setCommand() {
   string user_input; // store command

   cout << "$ ";
   getline(cin, user_input); // ask user for input
   
	if (cmd_controller) // dealloc. old command
		delete cmd_controller;
 
	cmd_controller = new Command();

	cmd_controller->init(user_input); // set parser's data member
   return;
}
