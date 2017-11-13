#include "exit.h"
#include <iostream>
#include <cstdlib>

Exit::Exit(){
    return;
}

Exit::~Exit(){
    return;
}

bool Exit::execute(){
	exit(0);
	return true;
}

void Exit::display(){
    std::cout << "exit (Special Command)" << std::endl;
}
