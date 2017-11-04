#include "user.h"

int main(){
    User* rshell = new User();
    while(true){
        rshell->setCommand();
    }
    
    return 0;
}