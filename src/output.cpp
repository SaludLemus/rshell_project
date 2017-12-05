#include "output.h"
#include <iostream>

Output::Output(){ }

Output::Output(Base* ln, Base* rn){ }

Output::~Output(){ }

bool Output::execute(){
    leftNode->execute();
    rightNode->execute();
    return true;
}

void Output::display(){
    leftNode->display();
    std::cout << "|" << std::endl;
    rightNode->display();
}