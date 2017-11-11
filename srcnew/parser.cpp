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

// Create tree
void Parser::createTree(){
	// Delete root in case it exists
	delete root;
	
	root = nextCommand();
	
	while(position != str.length()){
		Connector* newConnector = nextConnector();
		newConnector->setLeftNode(root);
		root = newConnector;
		
		newConnector->setRightNode(nextCommand());
	}
}

Base* Parser::getRoot(){
	return root;
}

Command* Parser::nextCommand(){
	if (str[position] == '#')
		return NULL;
	
	// tracks the last position of a word
	size_t endposition = position;
	// first tracks the starting position of a word then a modified last position
	size_t backtrackposition = position;
	int parameterSize = 0;
	
	// Get command array size
	do{
		backtrackposition = endposition;
		endposition = str.string::find(" ", endposition); // returns string::npos if not found
	}while(!checkCharSize(endposition, backtrackposition, parameterSize));
	
	// Create Parameter array
	char** commands = new char*[parameterSize + 1];
		
	// tracks the last position of a word
	size_t parsedendposition = position;
	// tracks the starting position of a word
	size_t initalposition = position;
	
	// Fill Parameter with char*'s
	for(int i = 0; i < parameterSize; i++){
		initalposition = parsedendposition;
		backtrackposition = parsedendposition;
		parsedendposition = str.string::find(" ", parsedendposition); // returns string::npos if not found
		returnEndForParameters(parsedendposition, backtrackposition);
		commands[i] = stringToCharStar(str.string::substr(initalposition, backtrackposition - initalposition));
	}
	
	// set the last array to null
	commands[parameterSize] = NULL;
	
	// Update position for next parse
	position = endposition;
	
	return new Command(commands);
}

Connector* Parser::nextConnector(){
	size_t startPosition = position;
	position = str.string::find(" ", position); // returns string::npos if not found
	
	if (position == string::npos){
		std::cout << "Error with parsing. Did you put an extra connector?" << std::endl;
		return NULL;
	}
	
	if (str[position - 1] == ';'){
		position++;
		return new Semicolon();
	}
	
	string connector = str.string::substr(startPosition, 2);
	if (connector == "&&"){
		position++;
		return new And();
	}
	if (connector == "||"){
		position++;
		return new Or();
	}
	
	std::cout << "Error with parsing. Did you forget a connector?" << std::endl;
	return NULL;
}

// Updates the endposition and parameter size. 
// Returns true when it reaches an end
bool Parser::checkCharSize(size_t & endposition, size_t backtrackposition, int & parameterSize) {
	// Check for comments
	if (str[backtrackposition] == '#'){
		endposition = str.length();
		return true;
	}
	
	// Check for end of program
	if (endposition == string::npos){
		endposition = str.length();
		parameterSize++;
		return true;
	}
	
	// Check for semicolons
	if(str[endposition - 1] == ';'){
		endposition = backtrackposition;
		parameterSize++;
		return true;
	}
	
	// Check for an alone && ||
	string connector = str.string::substr(backtrackposition, 2);
	if(connector == "&&" || connector == "||"){
		endposition = backtrackposition;
		return true;
	}
	
	// Get to beginning of next word, add to parameter size
	endposition++;
	parameterSize++;
	
	return false;
}

// Updates the backtrackpostion and endposition for the parser
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

// returns the char* equivalent of a string
char* Parser::stringToCharStar(const string & STR){
	char* cstr = new char[STR.length() + 1];
	strcpy(cstr, STR.c_str());
	return cstr;
}
