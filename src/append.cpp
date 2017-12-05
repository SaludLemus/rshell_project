#include "append.h"
#include <iostream>

Append::Append(){ }

Append::Append(Base* ln, Base* rn){ }

Append::~Append(){ }

bool Append::execute(){
    leftNode->execute();
    rightNode->execute();
    return true;
}

void Append::display(){
    leftNode->display();
    std::cout << "|" << std::endl;
    rightNode->display();
}