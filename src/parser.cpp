#include "parser.h"
#include <iostream>

using std::cout; using std::endl;

Parser::Parser() {
	str = "";
	position = 0;
	return;
}

Parser::Parser(const string &user_input) {
	str = user_input;
	position = 0;
	return;
}

void Parser::removeLastChar() {
	
	return;
}

// detects if the parsed phrase is the last. returns the enum value if it is the last.
int Parser::ifLast(size_t & newposition, size_t & lastposition) {
	
	if (newposition == string::npos){
		lastposition = str.length();
		return 0; // exitCC
	}
		
	if(str[newposition - 1] == ';'){
		lastposition = newposition - 1;
		return 1; // continueCC
	}
	if(str.string::substr(lastposition, 2) == "&&"){
		lastposition = newposition - 3;
		return 2; // andCC
	}
		
	if(str.string::substr(lastposition, 2) == "||"){
		lastposition = newposition - 3;
		return 3; // orCC
	}
	
	newposition++;
	
	return -1;
}

CommandLine* Parser::nextParse() {
	if (position == str.length())
			return 0;
	
	size_t newposition = position;
	size_t lastposition = position;
	int ifLastConnector = 0;
	
	do{
		lastposition = newposition;
		newposition = str.string::find(" ", newposition); // returns string::npos if not found
		ifLastConnector = ifLast(newposition, lastposition);
	}while(ifLastConnector == -1);
	
	string new_str = str.string::substr(position, lastposition - position);
	char* new_cmd = new char[new_str.size() + 1]; // alloc. mem.
	
	for (unsigned int i = 0; i < new_str.size(); ++i)
		new_cmd[i] = new_str.at(i); // get cmd from string
	new_cmd[new_str.size()] = '\0'; // append null term.
	
	
	CommandLine* CL = new CommandLine(new_cmd, static_cast<CommandConnector>(ifLastConnector));
	
	if (lastposition == str.size())
		position = str.size();
	else position = newposition + 1;
	
	
	
	return CL;
}
