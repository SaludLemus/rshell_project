#include "input.h"
#include <iostream>

Input::Input(){ }

Input::Input(Base* ln, Base* rn){ }

Input::~Input(){ }

bool Input::execute(){
    // display results
    std::cout << rightNode->getCommand() << std::endl;
    return true;
}

void Input::display(){
    
    std::cout << "<" << std::endl;
}