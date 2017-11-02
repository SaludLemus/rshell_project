#include "user.h"

int main(){
    User* rshell = new User();
    while(rshell->setCommand()){}
    
    return 0;
}