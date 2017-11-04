#include "user.h"

int main(){
    User* rshell = new User();
    
    while(rshell->setCommand()){}

    delete rshell;
    
    return 0;
}