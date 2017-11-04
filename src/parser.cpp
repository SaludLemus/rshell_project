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

// Updates the backtrackpostion and endposition. 
// Returns the int value of connector's enum value.
int Parser::checkConnectorForCommand(size_t & endposition, size_t & backtrackposition){
	
	// Check for comments
	if (str[backtrackposition] == '#'){
		endposition = str.length();
		return 0;
	}
	
	// Check for end
	if (endposition == string::npos){
		backtrackposition = str.length();
		return 0;
	}
	
	// Check for ; in end
	if (str[endposition - 1] == ';'){
		backtrackposition -= 1;
		return 1;
	}
	
	backtrackposition = endposition;
	endposition++;

	return -1;
}

// Updates the backtrackpostion, endposition, and parameter size. 
// Returns the int value of connector's enum value.
int Parser::checkConnectorForParameters(size_t & endposition, size_t & backtrackposition, int & parameterSize) {
	
	// Check for comments
	if (str[backtrackposition] == '#'){
		backtrackposition -= 2;
		endposition = str.length();
		return 0;
	}
	
	// Check for end of program
	if (endposition == string::npos){
		backtrackposition = str.length();
		parameterSize++;
		return 0; // endCC
	}
		
	// Check for ; in end
	if(str[endposition - 1] == ';'){
		backtrackposition = endposition - 1;
		parameterSize++;
		return 1; // continueCC
	}
	
	// Check for an alone &&
	if(str.string::substr(backtrackposition, 2) == "&&"){
		backtrackposition = endposition - 3;
		return 2; // andCC
	}
		
		
	// Check for an alone ||
	if(str.string::substr(backtrackposition, 2) == "||"){
		backtrackposition = endposition - 3;
		return 3; // orCC
	}
	
	endposition++;
	parameterSize++;
	
	return -1;
}

// Updates the backtrackpostion and endposition
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

// Returns a CommandLine* based on a parsed string within the class
CommandLine* Parser::nextParse() {
	// Return an exit if program parses nothing
	if (position == str.length())
			return new CommandLine(stringToCharStar(""), new char*[0], 0, exitCC);
	
	// Get Command
	size_t endposition = str.string::find(" ", position); // returns string::npos if not found
	size_t backtrackposition = position;
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
	
	// Create Parameter array
	char** parameters = NULL;
	if (parameterSize > 0)
		parameters = new char*[parameterSize];
		
	// Fill Parameter with char*'s
	size_t parsedendposition = initalposition;
	for(int i = 0; i < parameterSize; i++){
		initalposition = parsedendposition;
		backtrackposition = parsedendposition;
		parsedendposition = str.string::find(" ", parsedendposition); // returns string::npos if not found
		returnEndForParameters(parsedendposition, backtrackposition);
		parameters[i] = stringToCharStar(str.string::substr(initalposition, backtrackposition - initalposition));
	}
	
	CommandLine* CL = new CommandLine(command, parameters, parameterSize, static_cast<CommandConnector>(connector));
	
	// Update position for next parse
	if (endposition == str.length())
		position = str.length();
	else position = endposition + 1;
	
	return CL;
}

// returns the char* equivalent of a string
char* Parser::stringToCharStar(const string & STR){
	char* cstr = new char[STR.length() + 1];
	strcpy(cstr, STR.c_str());
	return cstr;
}
