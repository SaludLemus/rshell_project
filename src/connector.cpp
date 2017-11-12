
#include "connector.h"

Connector::Connector(){
    leftNode = 0;
    rightNode = 0;
}

Connector::Connector(Base* ln, Base* rn){
    leftNode = ln;
    rightNode = rn;
}

Connector::~Connector(){
    delete leftNode;
    delete rightNode;
}

void Connector::setLeftNode(Base* ln){
    leftNode = ln;
}

void Connector::setRightNode(Base* rn){
    rightNode = rn;
}