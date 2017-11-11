#include "semicolon.h"
#include <iostream>

Semicolon::Semicolon(){ }

Semicolon::Semicolon(Base* ln, Base* rn){ }

Semicolon::~Semicolon(){ }

bool Semicolon::execute(){
    leftNode->execute();
    return rightNode->execute();
}

void Semicolon::display(){
    leftNode->display();
    std::cout << ";" << std::endl;
    rightNode->display();
}