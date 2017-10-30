#ifndef __COMMANDLINE_H__
#define __COMMANDLINE_H__
#include <cstring>

enum CommandConnector{exitCC, next, success, fail};

class CommandLine{
    private:
        char* command;
        CommandConnector connector;
    
    public:
        CommandLine();
        CommandLine(char* _command, CommandConnector _connector);
    
        char* getCommand();
        CommandConnector getConnector();
};

#endif