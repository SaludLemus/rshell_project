#include "command.h"

Command::Command() : parse_cmd(0) {}

Command::~Command() {
	deallocParser();
	deallocCMDList();
}

void Command::init(const string &user_input) {
	deallocParser();
	parse_cmd = new Parse();
	
	parse_cmd->str.setString(user_input); // set Tokenizer's buffer
	
	commandIterator(); // start parse
	return;
}

void Command::commandIterator() {
	deallocCMDList();
	
	while (parse_cmd->nextParse() != "") // create commands from user's input
		cmd_list.push_back(new CommandLine(parse_cmd->current_parse));
	// loop through the list and execute command or exit
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
