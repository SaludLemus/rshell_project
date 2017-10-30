#ifndef __COMMANDLINE_H__
#define __COMMANDLINE_H__

enum CommandConnector{exitCC, next, success, fail};

class CommandLine{
    private:
        const char* command;
        CommandConnector connector;
    
    public:
        CommandLine();
        CommandLine(const char* _command, CommandConnector _connector)
            {command = _command; connector = _connector;}
    
        const char* getCommand() {return command;}
        CommandConnector getConnector() {return connector;}
};

CommandLine::CommandLine(){
    const char* c = "exit";
    command = c;
    connector = CommandConnector::exitCC;
}

#endif