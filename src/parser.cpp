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
int Parser::ifLast(size_t & newposition, size_t & lastposiiton) {
	
	if (newposition == string::npos){
		lastposiiton = str.length();
		return 0;
	}
		
	if(str[newposition - 1] == ';'){
		lastposiiton = newposition - 1;
		return 1;
	}
	if(str.string::substr(lastposiiton, 2) == "&&"){
		lastposiiton = newposition - 3;
		return 2;
	}
		
	if(str.string::substr(lastposiiton, 2) == "||"){
		lastposiiton = newposition - 3;
		return 3;
	}
	
	newposition++;
	
	return -1;
}

CommandLine* Parser::nextParse() {
	size_t newposition = position;
	size_t lastposiiton = position;
	int ifLastConnector = 0;
	
	do{
		lastposiiton = newposition;
		newposition = str.string::find(" ", newposition);
		ifLastConnector = ifLast(newposition, lastposiiton);
	}while(ifLastConnector == -1);
	
	CommandLine* CL = new CommandLine(str.string::substr(position, lastposiiton - position).c_str(), static_cast<CommandConnector>(ifLastConnector));
	
	position = newposition + 1;
	
	return CL;
}
