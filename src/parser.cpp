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
	
	// if program reaches some type of end, lastposition is set to correctly calculate the length for substr()
	// newposition is also set to correctly set the position variable for future parses
	
	// if program reaches definite end, do stuff
	if (newposition == string::npos){
		lastposiiton = str.length();
		return 0;
	}
		
	// if program reaches ;, do stuff
	if(str[newposition - 1] == ';'){
		lastposiiton = newposition - 1;
		return 1;
	}
	
	// if program reaches
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
	// Sanity check
	if (position == str.length())
		return NULL;
	
	size_t newposition = position; // Position from a found()
	size_t lastposiiton = position; // Postion of the last found(), used to backtrack
	
	int ifLastConnector = 0; // Connector
	
	do{
		lastposiiton = newposition; // Save newpostion into lastposition
		newposition = str.string::find(" ", newposition); // Get new newposition
		ifLastConnector = ifLast(newposition, lastposiiton); // Get new connector
	}while(ifLastConnector == -1); // Check if the program reached the end
	
	
	CommandLine* CL = new CommandLine(str.string::substr(position, lastposiiton - position).c_str(), static_cast<CommandConnector>(ifLastConnector));
	
	// if lastposition is string's length, then the parser reached the end
	if (lastposiiton == str.length()){
		position = str.length();
	}
	else{
		position = newposition + 1;
	}
		
	return CL;
}
