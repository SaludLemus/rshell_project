#include "command.h"
#include <cstdlib>
Command::Command() : parse_cmd(0) {}

Command::~Command() {
	deallocParser();
	deallocCMDList();
}

void Command::init(const string &user_input) {
	deallocParser();
	parse_cmd = new Parser(user_input);
	
	
	commandIterator(); // start parse
	return;
}

void Command::commandIterator() {
	deallocCMDList();
	CommandLine* new_cmd = 0;
	// use parse_cmd
	do {
		new_cmd = parse_cmd->nextParse(); // get command
		cmd_list.push_back(new DefaultCommand(new_cmd));

		if (cmd_list.at(cmd_list.size() - 1)->getConnector() == 0)
			break;
	} while (cmd_list.size() != 0 && cmd_list.at(cmd_list.size() - 1)->getConnector() != 0); // continue parsing until last command is reached or no input is entered
	
	for (unsigned int i = 0; i < cmd_list.size(); ++i) { // iterate through each cmd
		if (cmd_list.at(i)->getConnector() == 0) { // exitCC
			cmd_list.at(i)->execute();
			exitProg();
		}
		else if (cmd_list.at(i)->getConnector() == 1) // continueCC
			cmd_list.at(i)->execute();
		else if (cmd_list.at(i)->getConnector() == 2) {// andCC
			cmd_list.at(i)->execute();
			if (cmd_list.at(i)->checkStatus() == false) // skip next cmd
				++i;
		}
		else if (cmd_list.at(i)->getConnector() == 3) // orCC
			cmd_list.at(i)->execute();
			if (cmd_list.at(i)->checkStatus() == true) // skip next cmd
				++i;
		// cout << cmd_list.at(i)->getCMD() << endl; // null term.
	}
	
	return;
}

void Command::deallocParser() {
	if (parse_cmd)
		delete parse_cmd;
	return;
}


void Command::exitProg() {
	exit(0);
	return;
}


void Command::deallocCMDList() {
	for (unsigned int i = 0; i < cmd_list.size(); ++i)
		delete cmd_list.at(i);
	return;
}
