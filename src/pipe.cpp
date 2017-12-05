#include "pipe.h"
#include <iostream>

Pipe::Pipe(){ }

Pipe::Pipe(Base* ln, Base* rn){ }

Pipe::~Pipe(){ }

bool Pipe::execute(){
    leftNode->execute();
    rightNode->execute();
    return true;
}

void Pipe::display(){
    leftNode->display();
    std::cout << "|" << std::endl;
    rightNode->display();
}