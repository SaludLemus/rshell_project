#include "parser.h"
#include <iostream>
#include <string>

int main(){
    Parser* P = new Parser();
    string user_input = "";
    while(true){
        std::cout << "$ ";
        getline(cin, user_input);
        
        P->setString(user_input);
        P->createTree();
        P->getRoot()->execute();
    }
    
    delete P;
    
    return 0;
}