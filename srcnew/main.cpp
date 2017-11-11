#include "parser.h"

int main(){
    Parser* P = new Parser("echo hello world && FAILCOMMAND how are you doing && echo I'm #doing great");
    P->createTree();
    
    P->getRoot()->display();
    
    delete P;
    
    return 0;
}