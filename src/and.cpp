#include "and.h"
#include <iostream>

And::And(){ }

And::And(Base* ln, Base* rn){ }

And::~And(){ }

bool And::execute(){
    if(leftNode->execute()){
        return rightNode->execute();
    }
    
    return false;
}

void And::display(){
    leftNode->display();
    std::cout << "&&" << std::endl;
    rightNode->display();
}