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
	size_t newposition = position;
	size_t lastposition = position;
	int ifLastConnector = 0;
	
	do{
		lastposition = newposition;
		newposition = str.string::find(" ", newposition); // returns string::npos if not found
		ifLastConnector = ifLast(newposition, lastposition);
	}while(ifLastConnector == -1);
	
	CommandLine* CL = new CommandLine(str.string::substr(position, lastposition - position).c_str(), static_cast<CommandConnector>(ifLastConnector));
	
	position = newposition + 1;
	
	return CL;
}
