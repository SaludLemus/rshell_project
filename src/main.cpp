#include "parser.h"
#include <iostream>
#include <string>

int main(){
    Parser* P = new Parser();
    string user_input = "";
    unsigned i = 10;
    while(i > 0){
        std::cout << "$ ";
        getline(cin, user_input);
        
        P->setString(user_input);
        P->createTree();
        P->getRoot()->display();
        i--;
    }
    
    delete P;
    
    return 0;
}