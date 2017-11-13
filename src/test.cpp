#include "test.h"
#include <iostream>
#include <cstdlib>

Test::Test() : Command(){ }

Test::Test(char** cmdArray) : Command(cmdArray){}

Test::~Test() { }

bool Test::execute(){
	std::cout << "test " << commandArray[0] << " " << commandArray[1] << std::endl;
	return true;
}

void Test::display(){
    std::cout << "test " << commandArray[0] << " " << commandArray[1] << std::endl;
}
