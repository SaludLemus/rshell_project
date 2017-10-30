#include "commandline.h"

CommandLine::CommandLine(): command("exit"){
    connector = exitCC;
    return;
}

CommandLine::CommandLine(const char* _command, CommandConnector _connector): command(_command){
    connector = _connector;
    return;
}
    
CommandLine::~CommandLine(){
    delete command;
    return;
}
    
const char* CommandLine::getCommand() {
    return command;
}

CommandConnector CommandLine::getConnector() {
    return connector;
}
