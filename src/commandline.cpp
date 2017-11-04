#include "commandline.h"
#include <iostream>

CommandLine::CommandLine() { // "exit"
    connector = exitCC;
    return;
}

CommandLine::CommandLine(char** _command, unsigned _parameterSize, CommandConnector _connector) : command(_command){
    parameterSize = _parameterSize;
    connector = _connector;
    return;
}
    
CommandLine::~CommandLine(){
	delete[] command;
    return;
}
    
char** CommandLine::getCommand() {
    return command;
}

CommandConnector CommandLine::getConnector() {
    return connector;
}

// Test function
void CommandLine::display(){
	for(unsigned i = 0; i < parameterSize; i++)
		std::cout << command[i] << " ";
	std::cout << "NULL" << "|" << connector << std::endl;
}