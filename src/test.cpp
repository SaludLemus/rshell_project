#include "test.h"
#include <iostream>
#include <cstdlib>
#include "command.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
Test::Test(){
    return;
}

Test::~Test(){
    return;
}

bool Test::execute(){
	struct stat flag_handler; // for -e, -f, -d
		
	// handle error -1
	//if (stat()
	// determine flag type 

	// -e
		// if true, print true
		// else false
	
	// -f
		// if true, print true
		// else false
	
	// -d
		// if true, print true
		
		// else false
		
    return true;
	
}

void Test::display(){
    Command::display(); // call base class
    return;
}
