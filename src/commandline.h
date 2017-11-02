#ifndef __COMMANDLINE_H__
#define __COMMANDLINE_H__
#include <cstring>

enum CommandConnector{exitCC, continueCC, andCC, orCC};

class CommandLine {
    private:
        char* command;
        CommandConnector connector;
    
    public:
        CommandLine();
        CommandLine(char* _command, CommandConnector _connector);
        ~CommandLine();
    
        char* getCommand();
        CommandConnector getConnector();
};

#endif
