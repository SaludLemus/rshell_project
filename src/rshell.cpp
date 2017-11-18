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

// Debug
// int main(){
//     Parser* P = new Parser();
//     string user_input = "";
//     int i = 1;
//     while(i > 0){
//         std::cout << "$ ";
//         getline(cin, user_input);
        
//         P->setString(user_input);
//         P->createTree();
//         P->getRoot()->display();
//         i--;
//     }
    
//     delete P;
    
//     return 0;
// }