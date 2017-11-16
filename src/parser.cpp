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

void Parser::setString(const string &user_input){
	str = user_input;
	position = 0;
	return;
}

// Create tree
void Parser::createTree(){
	// Delete root in case it exists
	delete root;
	
	root = nextCommand();
	
	while(position < str.length()){
		Connector* newConnector = nextConnector();
		newConnector->setLeftNode(root);
		root = newConnector;
		
		newConnector->setRightNode(nextCommand());
	}
}

Base* Parser::getRoot(){
	return root;
}

Base* Parser::nextCommand(){
	// Check for special cases
	Base* spcCMD = returnSpecialCommand();
	if (spcCMD != NULL)
		return spcCMD;

	// tracks the last position of a word
	size_t endposition = position;
	// first tracks the starting position of a word then a modified last position
	size_t backtrackposition = position;
	// parameter size
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
	
	//std::cout << "Position[" << startPosition << "|" << position << "]" << std::endl;
	
	if (position == string::npos){
		std::cout << "Error with parsing. Did you leave extra spaces?" << std::endl;
		return NULL;
	}
	
	if (str[startPosition] == ';'){
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
	
	std::cout << "Error with parsing at connector. This shouldn't happen." << std::endl;
	std::cout << "Connector string check [" << connector << "]" << std::endl;
	std::cout << "Semicolon check [" << str[startPosition] << "]" << std::endl;
	std::cout << "Position[" << startPosition << "|" << position << "]" << std::endl;
	return NULL;
}

Base* Parser::returnSpecialCommand(){
	// check parathesis
	if(str[position] == '('){
		position++;
		return returnTreeCommand();
	}
	
	string command = str.string::substr(position, 4);
	
	// check exit
	if (command == "exit"){
		size_t backtrackposition = position;
		size_t endposition = str.string::find(" ", position);
		int parameterSize = 0;
		checkCharSize(endposition, backtrackposition, parameterSize);
		
		position = endposition;
		return new Exit();
	}
	
	// check if test (test version)
	if (command == "test"){
		// mirrors the procedure of the original parser, but slightly modified
		size_t endposition = position;
		size_t backtrackposition = position;
		int parameterSize = 0;
			
		do{
			backtrackposition = endposition;
			endposition = str.string::find(" ", endposition); // returns string::npos if not found
		}while(!checkCharSize(endposition, backtrackposition, parameterSize));
		
		char** commandArray = new char*[3];
		
		size_t parsedendposition = position;
		size_t initalposition = position;
		int i = 0;	//index
		
		// skip once for test
		backtrackposition = parsedendposition;
		parsedendposition = str.string::find(" ", parsedendposition); // returns string::npos if not found
		returnEndForParameters(parsedendposition, backtrackposition);
		
		// parameter size = 2 (autofill to -e)
		if (parameterSize == 2){
			commandArray[i] = stringToCharStar("-e");
			i++;
		}
		
		// fill last two (or one) spots
		while(i < 2){
			initalposition = parsedendposition;
			backtrackposition = parsedendposition;
			parsedendposition = str.string::find(" ", parsedendposition); // returns string::npos if not found
			returnEndForParameters(parsedendposition, backtrackposition);
			commandArray[i] = stringToCharStar(str.string::substr(initalposition, backtrackposition - initalposition));
			i++;
		}
		
		// set the last array to null
		commandArray[i] = NULL;
	
		// Update position for next parse
		position = endposition;
		
		return new Test(commandArray);
	}
	
	// check if test ([] verstion)
	if (str[position] == '['){
		// mirrors the procedure of the original parser, but slightly modified
		
		position += 2; // move position cursor, past [
		
		size_t endposition = position;
		size_t backtrackposition = position;
		int parameterSize = 0;
			
		do{
			backtrackposition = endposition;
			endposition = str.string::find(" ", endposition); // returns string::npos if not found
		}while(!checkCharSize(endposition, backtrackposition, parameterSize));
		
		char** commandArray = new char*[3];
		
		size_t parsedendposition = position;
		size_t initalposition = position;
		int i = 0;	//index
		
		// parameter size = 1 (autofill to -e)
		if (parameterSize == 1){
			commandArray[i] = stringToCharStar("-e");
			i++;
		}
		
		// fill last two (or one) spots
		while(i < 2){
			initalposition = parsedendposition;
			backtrackposition = parsedendposition;
			parsedendposition = str.string::find(" ", parsedendposition); // returns string::npos if not found
			returnEndForParameters(parsedendposition, backtrackposition);
			commandArray[i] = stringToCharStar(str.string::substr(initalposition, backtrackposition - initalposition));
			i++;
		}
		
		// set the last array to null
		commandArray[i] = NULL;
	
		// Update position for next parse
		position = endposition;
		
		return new Test(commandArray);
	}
	
	// check if empty
	if (position == str.length()){
		return new Command();
	}
	
	return NULL;
}

Base* Parser::returnTreeCommand(){

	Base* treeRoot = nextCommand();
	
	while(str[position] != ')'){
		Connector* newConnector = nextConnector();
		newConnector->setLeftNode(treeRoot);
		treeRoot = newConnector;
		
		newConnector->setRightNode(nextCommand());
	}
	if (str[position + 1] == ' ')
		position += 2;
	else
		position++;
		
	
	return treeRoot;
}

// Updates the endposition and parameter size. 
// Returns true when it reaches an end
bool Parser::checkCharSize(size_t & endposition, size_t backtrackposition, int & parameterSize) {
	if (endposition == string::npos){
		endposition = str.length();
	}
	
	char firstLetter = str[backtrackposition];
	
	// Check for comments
	if (firstLetter == '#'){
		endposition = str.length();
		return true;
	}
	
	// Check for end of test
	if (firstLetter == ']'){
		if (endposition == string::npos){
			endposition = str.length();
		}
		else{
			endposition += 1;
		}
		return true;
	}
	
	// Check for semicolons or ending parathesis
	char endingChar = str[endposition - 1];
	if(endingChar == ';' || endingChar == ')'){
		parameterSize++;
		do{
			endposition -= 1;
			endingChar = str[endposition - 1];
		}while(endingChar == ';' || endingChar == ')');
		
		return true;
	}
	
	// Check for an alone && ||
	string connector = str.string::substr(backtrackposition, 2);
	if(connector == "&&" || connector == "||"){
		endposition = backtrackposition;
		return true;
	}
	
	// Check for end of program
	if (endposition == str.length()){
		parameterSize++;
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
		endposition = str.length();
	}
		
	// Make the backtrackposition be before all '(' and ';'
	char endingChar = str[endposition - 1];
	if(endingChar == ';' || endingChar == ')'){
		backtrackposition = endposition;
		do{
			backtrackposition -= 1;
			endingChar = str[backtrackposition - 1];
		}while(endingChar == ';' || endingChar == ')');
		
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
