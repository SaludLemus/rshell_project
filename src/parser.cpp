#include "parser.h"
#include <iostream>
#include <cstdlib>

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

Parser::~Parser(){
	delete root;
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

// A parser that specifically looks for commands, parathesis, and special commands
// Returns a Base* of the next command it sees, starting from the position
Base* Parser::nextCommand(){
	// Check for special commands (i.e exit, test, parathesis)
	Base* spcCMD = returnSpecialCommand();
	if (spcCMD != NULL)
		return spcCMD;

	// The parser uses two position trackers:
	// startingposition is the position at the beginning of the word
	// endposition is the position at the end of the word
	 
	size_t startingposition = position;
	size_t endposition = position;
	
	// Execvp function requires a char* array, as such, the array size needs to be 
	// calculated beforehand
	int parameterSize = 0;
		
	// Get command array size
	do{
		startingposition = endposition;
		endposition = str.string::find(" ", endposition); /* CHANGE TO A BETTER WORD SEARCH LATER */
	}while(!checkCharSize(endposition, startingposition, parameterSize));
	
	// Create Parameter array
	char** commands = new char*[parameterSize + 1];
		
	// The parser has two additional position trackers
	// parsedendposition is the position at the end of the word, separate of the
	// endposition variable (endposition is used to set the position for next parse)
	// backtrackposition is a modified position at the end of the word, used
	// so the substring ignores ';' and ')'
	size_t backtrackposition = position;
	size_t parsedendposition = position;
	
	// Fill Parameter with char*'s
	for(int i = 0; i < parameterSize; i++){
		startingposition = parsedendposition;
		backtrackposition = parsedendposition;
		parsedendposition = str.string::find(" ", parsedendposition); /* CHANGE TO A BETTER WORD SEARCH LATER */
		returnEndForParameters(parsedendposition, backtrackposition, startingposition);
		commands[i] = stringToCharStar(str.string::substr(startingposition, backtrackposition - startingposition));
	}
	
	// set the last array index to null
	commands[parameterSize] = NULL;
	
	// Update position for next parse
	position = endposition;
	
	return new Command(commands);
}

// A parser that specifically looks for connector
// Returns a Connector* of the next connector it sees, starting from the position
Connector* Parser::nextConnector(){
	size_t startPosition = position;
	position = str.string::find(" ", position); // sets the position for the next parse
	
	// This never seems to happen
	if (position == string::npos){
		std::cout << "Error with parsing. Did you leave extra spaces?" << std::endl;
		return NULL;
	}
	
	// Return a Semicolon*, Input*, Output*, or Pipe* if either of the single char are found
	char singleChar = str[startPosition];
	if (singleChar == ';'){
		position++;
		return new Semicolon();
	}
	if (singleChar == '>'){
		position++;
		return new Output();
	}
	if (singleChar == '<'){
		position++;
		return new Input();
	}
	if (singleChar == '|'){
		position++;
		return new Pipe();
	}
	
	// Return an And*, Or* or Append* if either of the strings are found
	string connector = str.string::substr(startPosition, 2);
	if (connector == "&&"){
		position++;
		return new And();
	}
	if (connector == "||"){
		position++;
		return new Or();
	}
	if (connector == ">>"){
		position++;
		return new Append();
	}
	
	std::cout << "Error with parsing at connector. Did you leave extra spaces?. Unequal parathesis?" << std::endl;
	exit(1);
	return NULL;
}

// A helper parser of nextCommand() that specifically looks for special commands
// Should never be used by itself, use nextCommand() instead
// Returns a Base* of the next special command it sees, starting from the position
// Returns NULL if no special command is found
Base* Parser::returnSpecialCommand(){
	// Returns a Base* if the first letter is an open parathesis "("
	if(str[position] == '('){
		position++;
		return returnTreeCommand();
	}
	
	string command = str.string::substr(position, 4);
	
	// Returns an Exit* if the exectuable is specifically exit
	if (command == "exit"){
		size_t backtrackposition = position;
		size_t endposition = str.string::find(" ", position);
		int parameterSize = 0;
		checkCharSize(endposition, backtrackposition, parameterSize);
		
		position = endposition;
		return new Exit();
	}
	
	// Returns a Test* if the exectuable is specifically test
	if (command == "test"){
		// mirrors the procedure of the original parser, but slightly modified
		size_t startingposition = position;
		size_t endposition = position;
		int parameterSize = 0;
			
		do{
			startingposition = endposition;
			endposition = str.string::find(" ", endposition);
		}while(!checkCharSize(endposition, startingposition, parameterSize));
		
		char** commandArray = new char*[3];
		
		size_t parsedendposition = position;
		size_t backtrackposition = position;
		int i = 0;	//index
		
		// skip once for test
		backtrackposition = parsedendposition;
		parsedendposition = str.string::find(" ", parsedendposition);
		returnEndForParameters(parsedendposition, backtrackposition, startingposition);
		
		// autofill to -e if the parameter size is 2
		if (parameterSize == 2){
			commandArray[i] = stringToCharStar("-e");
			i++;
		}
		
		// fill last two (or one) spots
		while(i < 2){
			startingposition = parsedendposition;
			backtrackposition = parsedendposition;
			parsedendposition = str.string::find(" ", parsedendposition); // returns string::npos if not found
			returnEndForParameters(parsedendposition, backtrackposition, startingposition);
			commandArray[i] = stringToCharStar(str.string::substr(startingposition, backtrackposition - startingposition));
			i++;
		}
		
		// set the last array to null
		commandArray[i] = NULL;
	
		// Update position for next parse
		position = endposition;
		
		return new Test(commandArray);
	}
	
	// Returns a Test* if the first letter is an open bracket "["
	if (str[position] == '['){
		// mirrors the procedure of the original parser, but slightly modified
		position += 2; // move position cursor, past [
		
		size_t startingposition = position;
		size_t endposition = position;
		int parameterSize = 0;
			
		do{
			startingposition = endposition;
			endposition = str.string::find(" ", endposition);
		}while(!checkCharSize(endposition, startingposition, parameterSize));
		
		char** commandArray = new char*[3];
		
		size_t parsedendposition = position;
		size_t backtrackposition = position;
		int i = 0;	//index
		
		// autofill to -e if the parameter size is 2
		if (parameterSize == 1){
			commandArray[i] = stringToCharStar("-e");
			i++;
		}
		
		// fill last two (or one) spots
		while(i < 2){
			startingposition = parsedendposition;
			backtrackposition = parsedendposition;
			parsedendposition = str.string::find(" ", parsedendposition); // returns string::npos if not found
			returnEndForParameters(parsedendposition, backtrackposition, startingposition);
			commandArray[i] = stringToCharStar(str.string::substr(startingposition, backtrackposition - startingposition));
			i++;
		}
		
		// set the last array to null
		commandArray[i] = NULL;
	
		// Update position for next parse
		position = endposition;
		
		return new Test(commandArray);
	}
	
	// Returns an empty command if the position overextends the parser
	// Should never be reached as the function would break before reaching here
	if (position >= str.length()){
		return new Command();
	}
	
	return NULL;
}

// A recursive helper parser of returnSpecialCommand() that specifically looks for parathesis
// Should never be used by itself, use returnSpecialCommand() instead
// Creates a "new" root from the open parathesis until it sees a close parathesis
// Returns a Base* root of the next commands and connectors it sees, starting from the position
Base* Parser::returnTreeCommand(){

	Base* treeRoot = nextCommand();
	
	while(str[position] != ')'){
		Connector* newConnector = nextConnector();
		newConnector->setLeftNode(treeRoot);
		treeRoot = newConnector;
		
		newConnector->setRightNode(nextCommand());
	}
	
	// Updates the position for the next parse/next returnTreeCommand
	if (str[position + 1] == ' ')
		position += 2;
	else
		position++;
		
	
	return treeRoot;
}

// A helper parser of nextFunctions that updates the endposition and parameter size. 
// Returns true when it reaches an end (i.e. comments, connectors, closing brackets/parathesis)
bool Parser::checkCharSize(size_t & endposition, size_t startingposition, int & parameterSize) {
	
	// Fix the endposition before going any further
	if (endposition == string::npos){
		endposition = str.length();
	}
	
	char firstLetter = str[startingposition];
	
	// Check for comments
	if (firstLetter == '#'){
		endposition = str.length();
		return true;
	}
	
	// Check for end of test
	if (firstLetter == ']'){
		if (startingposition + 1 != endposition){
			endposition = startingposition + 1;
		}
		else{
			endposition++;
		}
		return true;
	}
	
	// Check for quotations
	if (firstLetter == '\"'){
		endposition = startingposition + 1;
		do{
			endposition++;
		}while(str[endposition] != '\"');
		
		endposition++;
	}
	
	// Check for semicolons or ending parathesis
	// Update the endposition until it doesnt reference a semicolon or parathesis
	char endingChar = str[endposition - 1];
	if(endingChar == ';' || endingChar == ')'){
		parameterSize++;
		do{
			endposition -= 1;
			endingChar = str[endposition - 1];
		}while(endingChar == ';' || endingChar == ')');
		
		return true;
	}
	
	// Check for an alone && || >>
	// Check for an alone > < |
	string connector = str.string::substr(startingposition, 2);
	if(connector == "&&" || connector == "||" || connector == ">>" || 
		firstLetter == '|' || firstLetter == '>' || firstLetter == '<'){
		endposition = startingposition;
		return true;
	}
	
	// Check for end of program
	if (endposition >= str.length()){
		parameterSize++;
		return true;
	}
	
	// Get to beginning of next word, add to parameter size
	endposition++;
	parameterSize++;
	
	return false;
}

// A helper parser of nextFunctions that updates the endposition and backtrackposition.
// Used to get the correct substring of a word (due to ';' and ')')
// Returns nothing
void Parser::returnEndForParameters(size_t & endposition, size_t & backtrackposition, size_t & startingposition) {
	
	if (endposition == string::npos){
		endposition = str.length();
	}

	// Do quotation stuff
	if (str[startingposition] == '\"'){
		startingposition++;
		do{
			backtrackposition++;
		}while(str[backtrackposition] != '\"');
	
		if (backtrackposition == str.length()){
			endposition = backtrackposition;
		}
		else if (str[backtrackposition + 1] == ' '){
			endposition = backtrackposition + 2;
		}
		else{
			endposition = backtrackposition + 1;
		}
	
		return;
	}
		
	// Make the backtrackposition be before all ')' and ';'
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

// Returns the char* equivalent of a string
char* Parser::stringToCharStar(const string & STR){
	char* cstr = new char[STR.length() + 1];
	strcpy(cstr, STR.c_str());
	return cstr;
}
