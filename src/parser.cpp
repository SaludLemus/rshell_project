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

int Parser::checkConnectorForCommand(size_t & endposition, size_t & backtrackposition){
	if (endposition == string::npos){
		backtrackposition = str.length();
		return 0;
	}
	
	if (str[endposition - 1] == ';'){
		backtrackposition -= 1;
		return 1;
	}
	
	endposition++;

	return -1;
}

// detects if the parsed phrase is the last. returns the enum value if it is the last.
int Parser::checkConnectorForParameters(size_t & endposition, size_t & backtrackposition, int & parameterSize) {
	
	if (endposition == string::npos){
		backtrackposition = str.length();
		parameterSize++;
		return 0; // endCC
	}
		
	if(str[endposition - 1] == ';'){
		backtrackposition = endposition - 1;
		parameterSize++;
		return 1; // continueCC
	}
	if(str.string::substr(backtrackposition, 2) == "&&"){
		backtrackposition = endposition - 3;
		return 2; // andCC
	}
		
	if(str.string::substr(backtrackposition, 2) == "||"){
		backtrackposition = endposition - 3;
		return 3; // orCC
	}
	
	endposition++;
	parameterSize++;
	
	return -1;
}

void Parser::returnEndForParameters(size_t & endposition, size_t & backtrackposition) {
	
	if (endposition == string::npos){
		backtrackposition = str.length();
		return;
	}
		
	if(str[endposition - 1] == ';'){
		backtrackposition = endposition - 1;
		return;
	}

	backtrackposition = endposition;
	endposition++;
}

CommandLine* Parser::nextParse() {
	if (position == str.length())
			return 0;
	
	// Get Command
	size_t endposition = str.string::find(" ", position); // returns string::npos if not found
	size_t backtrackposition = endposition;
	int connector = checkConnectorForCommand(endposition, backtrackposition);
	char* command = stringToCharStar(str.string::substr(position, backtrackposition - position));
	
	// Get Array Size for Parameter
	int parameterSize = 0;
	size_t initalposition = endposition;
	if (connector == -1){
		while(connector == -1){
			backtrackposition = endposition;
			endposition = str.string::find(" ", endposition); // returns string::npos if not found
			connector = checkConnectorForParameters(endposition, backtrackposition, parameterSize);
		}
	}	
	
	// Fill Parameter with char*'s
	char** parameters = new char*[parameterSize];
	endposition = initalposition;
	for(int i = 0; i < parameterSize; i++){
		initalposition = endposition;
		backtrackposition = endposition;
		endposition = str.string::find(" ", endposition); // returns string::npos if not found
		returnEndForParameters(endposition, backtrackposition);
		parameters[i] = stringToCharStar(str.string::substr(initalposition, backtrackposition - initalposition));
	}
	
	CommandLine* CL = new CommandLine(command, parameters, parameterSize, static_cast<CommandConnector>(connector));
	
	// Update position for next parse
	if (endposition == str.length())
		position = str.length();
	else if (connector >= 2)
		position = endposition + 3;
	else position = endposition + 1;
	
	return CL;
}

char* Parser::stringToCharStar(const string & STR){
	char* cstr = new char[STR.length() + 1];
	strcpy(cstr, STR.c_str());
	return cstr;
}
