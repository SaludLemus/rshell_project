#include "commandline.h"
#include <iostream>

CommandLine::CommandLine(): command("exit"){
    connector = exitCC;
    return;
}

CommandLine::CommandLine(const char* _command, CommandConnector _connector): command(_command){
    connector = _connector;
    return;
}
    
CommandLine::~CommandLine(){
    //delete command;
    return;
}
    
const char* CommandLine::getCommand() {
    return command;
}

CommandConnector CommandLine::getConnector() {
    return connector;
}

void CommandLine::display(){
    std::cout << command << " " << connector << std::endl;
}