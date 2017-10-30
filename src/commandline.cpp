#include "commandline.h"

CommandLine::CommandLine(){
    strncpy(command, "exit", 3);
    connector = exitCC;
    return;
}

CommandLine::CommandLine(char* _command, CommandConnector _connector){
    command = _command; 
    connector = _connector;
    return;
}
    
char* CommandLine::getCommand() {
    return command;
}

CommandConnector CommandLine::getConnector() {
    return connector;
}
