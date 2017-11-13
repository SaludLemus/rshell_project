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
		
	// commandArray[0] is the flag type; commandArray[1] is the file path	
		
	
	if (stat(commandArray[1], &flag_handler) == -1) { // handle error -1, errno
		if (errno == EACCES) // search permission is denied in the path
			perror("Search permission is denied for one of the directories.");
		else if (errno == ELOOP) // too many symbolic links while traversing
			perror("Too many symbolic links while traversing.");
		else if (errno == ENAMETOOLONG) // path is too long
			perror("Path is too long.");
		else if (errno == ENOENT) // path is empty or component of path DNE
			perror("Component of path does not exits.");
		else if (errno == ENOTDIR) // component of path prefix of path is not a dir.
			perror("Component of path is not a directory.");
		exit(EXIT_FAILURE); // error
	}
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
