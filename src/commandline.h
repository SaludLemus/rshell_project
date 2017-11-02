#ifndef __COMMANDLINE_H__
#define __COMMANDLINE_H__
#include <cstring>

enum CommandConnector{exitCC, next, success, fail};

class CommandLine{
    private:
        const char* command;
        CommandConnector connector;
    
    public:
        CommandLine();
        CommandLine(const char* _command, CommandConnector _connector);
        ~CommandLine();
    
        const char* getCommand();
        CommandConnector getConnector();
        void display();
};

#endif