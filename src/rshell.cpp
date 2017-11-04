#include "user.h"

int main(){
    User* rshell = new User();
    
    rshell->setCommand();

    delete rshell;
    
    return 0;
}