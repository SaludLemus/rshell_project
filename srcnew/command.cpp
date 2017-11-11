#include "command.h"
#include <iostream>

Command::Command(){
    commandArray = 0;
}

Command::Command(char** cmdArray){
    commandArray = cmdArray;
}

Command::~Command(){
    delete[] commandArray;
}

bool Command::execute(){
    return true;
}

void Command::display(){
    unsigned index = 0;
    while(commandArray[index] != NULL){
        std::cout << commandArray[index] << " ";
        index++;
    }
    std::cout << std::endl;
}