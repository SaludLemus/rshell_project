#include "or.h"
#include <iostream>

Or::Or(){ }

Or::Or(Base* ln, Base* rn){ }

Or::~Or(){ }

bool Or::execute(){
    if(leftNode->execute()){
        return false;
    }
    return rightNode->execute();
}

void Or::display(){
    leftNode->display();
    std::cout << "||" << std::endl;
    rightNode->display();
}