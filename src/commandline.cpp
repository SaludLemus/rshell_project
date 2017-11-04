#include "commandline.h"
#include <iostream>

CommandLine::CommandLine() { // "exit"
	 command = new char[5];
	 command[0] = 'e';
	 command[1] = 'x';
	 command[2] = 'i';
	 command[3] = 't';
	 command[4] = '\0';
    connector = exitCC;
    return;
}

CommandLine::CommandLine(char* _command, char* _parameters[], unsigned _parameterSize, CommandConnector _connector) : command(_command), parameters(_parameters){
    parameterSize = _parameterSize;
    connector = _connector;
    return;
}
    
CommandLine::~CommandLine(){
	delete command;
	delete[] parameters;
    return;
}
    
char* CommandLine::getCommand() {
    return command;
}

char** CommandLine::getParameters(){
	return parameters;
}

CommandConnector CommandLine::getConnector() {
    return connector;
}

// Test function
void CommandLine::display(){
	std::cout << command << "|" << parameterSize << "|";
	for(unsigned i = 0; i < parameterSize; i++)
		std::cout << parameters[i] << " ";
	std::cout << "|" << connector << std::endl;
}