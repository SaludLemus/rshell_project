#ifndef __COMMANDLINE_H__
#define __COMMANDLINE_H__
#include <cstring>

enum CommandConnector{exitCC, continueCC, andCC, orCC};

class CommandLine {
    private:
        char** command;
        CommandConnector connector;
        unsigned parameterSize;
    
    public:
        CommandLine();
        CommandLine(char** _command, unsigned parameterSize, CommandConnector _connector);
        ~CommandLine();
    
        char** getCommand();
        CommandConnector getConnector();

        void display();
};

#endif
