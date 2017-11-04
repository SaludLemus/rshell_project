#ifndef __COMMANDLINE_H__
#define __COMMANDLINE_H__
#include <cstring>

enum CommandConnector{exitCC, continueCC, andCC, orCC};

class CommandLine {
    private:
        char* command;
        char** parameters;
        CommandConnector connector;
        unsigned parameterSize;
    
    public:
        CommandLine();
        CommandLine(char* _command, char* _parameters[], unsigned parameterSize, CommandConnector _connector);
        ~CommandLine();
    
        char* getCommand();
        char** getParameters();
        CommandConnector getConnector();
        
        void display();
};

#endif
