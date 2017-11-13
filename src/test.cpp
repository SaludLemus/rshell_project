#include "test.h"
#include <iostream>
#include <cstdlib>

Test::Test(){
    return;
}

Test::~Test(){
    return;
}

bool Test::execute(){
	std::cout << "Performed Test Case" << std::endl;
	return true;
}

void Test::display(){
    std::cout << "test" << std::endl;
}
