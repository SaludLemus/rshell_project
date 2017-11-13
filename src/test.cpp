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
using namespace std;

Test::Test() : Command(){ }

Test::Test(char** cmdArray) : Command(cmdArray){}

Test::~Test() { }

bool Test::execute(){
	struct stat flag_handler; // for -e, -f, -d
	bool stat_success = true; // for -e
	
	// commandArray[0] is the flag type; commandArray[1] is the file path	
		
	// stat(const char* path, struct stat* buf)
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
			
		else // handle all other errors
			perror("Error, file/directory specified can not be completed.");
			
		stat_success = false;
		exit(EXIT_FAILURE); // error
	}
	
	char* flag_type = commandArray[0]; // determine flag type 
	
	if (flag_type[1] == 'e') { // -e case
		if (stat_success) { // file/directory exists
			cout << "(True)" << endl;
			return true;
		}
		else
			return false;
	}
	
	else if (flag_type[1] == 'f') { 	// -f case
		// S_ISREG(mode_t) returns non-zero int if true
		if (S_ISREG(flag_handler.st_mode) != 0) {
			cout << "(True)" << endl;
			return true;
		}
		else
			return false;
	}
	
	else if (flag_type[1] == 'd') { // -d case
		// S_ISDIR(mode_t) returns non-zero int if true
		if (S_ISDIR(flag_handler.st_mode) != 0) {
			cout << "(True)" << endl;
			return true;
		}
		else
			return false;
	}
	
	else {// flag_type[1] does not match any of the flags
		cout << "Flag type does not match" << endl;
		exit(EXIT_FAILURE); // error
	}
		
    return false;
}

void Test::display(){
    std::cout << "test " << commandArray[0] << " " << commandArray[1] << std::endl;
    return;
}
