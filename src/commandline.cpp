#include "commandline.h"

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

CommandLine::CommandLine(char* _command, CommandConnector _connector): command(_command){
    connector = _connector;
    return;
}
    
CommandLine::~CommandLine(){
    delete[] command;
    return;
}
    
char* CommandLine::getCommand() {
    return command;
}

CommandConnector CommandLine::getConnector() {
    return connector;
}
