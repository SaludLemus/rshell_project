#include "command.h"
#include <cstdlib>
Command::Command() : parse_cmd(0) {}

Command::~Command() {
	deallocParser();
	deallocCMDList();
}

void Command::init(const string &user_input) {
	deallocParser();
	parse_cmd = new Parse(user_input);
	
	
	commandIterator(); // start parse
	return;
}

void Command::commandIterator() {
	deallocCMDList();
	CommandLine* current_command = parse_cmd->nextParse();
	CommandLine* prev_command = 0; // for connectors
	
	//while (true) {// create commands from user's input
		//cmd_list.push_back(current_command);
		
		//if (current_command->getConnector() == exitCC) { // reached end of command
			// execute command and then exit
			//exit();
		//}
		
		
		//prev_command = current_command;
		//current_command = parse_cmd->nextParse(); // get next command
	//}
	// loop through the list and execute command or exit
	
	do {
		current_command = parse_cmd->nextParse();
		cmd_list.push_back(current_command);
	}
	while (current_command->getConnector() != exitCC); // continue getting commands until end of input
	
	for (list<CommandLine*>::iterator itr = cmd_list.begin(); itr != cmd_list.end(); ++itr) {
		if ((*itr)->getConnector() == success || (*itr)->getConnector() == fail) { // handle AND or ||
			// check prev_command ptr for a sucess or failure and execute based on that
			prev_command = (*itr); // for the next command
		}
		// handle exitCC
		// handle next
	}
	return;
}

void Command::exit() {
	exit(0); // end program
	return;
}

void Command::deallocParser() {
	if (parse_cmd)
		delete parse_cmd;
	return;
}


void Command::deallocCMDList() {
	for (list<CommandLine*>::iterator itr = cmd_list.begin(); itr !+ cmd_list.end(); ++itr)
		delete (*itr);
	return;
}
