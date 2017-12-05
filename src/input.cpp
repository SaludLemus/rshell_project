#include "input.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <iostream>
using namespace std;
Input::Input(){file_name = 0;}

Input::Input(Base* ln, Base* rn){file_name = rn->getCommand();}

Input::~Input(){file_name = 0;}

bool Input::execute(){
   if (leftNode && rightNode) { // child exists
		int save_0 = dup(0);
	
		// check dup()
		if (!check_dup(save_0))
			return false;
		
		// close [0] and check
		if (!check_close())
			return false;
		
		// set fd for file to [0] and check
		if (!change_input())
			return false;
		
		// check execute()
		if (!leftNode->execute())
			return false;
		
		// restore save_0 and check
		if (!restore_save0(save_0))
			return false;
	
		return true;
	}

	return false;
}

void Input::display(){
    
    std::cout << "<" << std::endl;
}

bool Input::check_dup(int save_0) {
	if (save_0 == -1) { // dup() failed and errno is set
		if (errno == EBADF)
			cout << "New fd is out of the allowed range." << endl;
		
		cout << "Dup() failed.)" << endl;
		return false;
	}
	return true;
}

bool Input::check_close() {
	if (close(0) == -1) { // close() failed and errno is set
		if (errno == EBADF)
			cout << "Fd is not a valid fd." << endl;
		if (errno == EINTR)
			cout << "Interrupted by a signal." << endl;
		if (errno == EIO)
			cout << "I/O error occured." << endl;
		
		cout << "Close() failed." << endl;
	
		return false;
	}
	return true;
}

bool Input::change_input() {
	// open(const char* FILE_NAME, INT FLAGS)
	// file will be read only and FILE HAS TO EXIST!
	if (open(file_name, O_WRONLY) == -1) { // open() failed and errno is set
		if (errno == EACCES)
			cout << "File access not allowed; File does not exist." << endl;
		if (errno == ELOOP)
			cout << "Too many symbolic links were encountered." << endl;
		if (errno == ENFILE)
			cout << "System-wide limit on number of open files has been reached." << endl;
	
		cout << "Open() failed." << endl;
		return false;
	}
	return false;
}

bool Input::restore_save0(int save_0) {
	if (dup2(save_0, 0) == -1 || close(save_0) == -1) { // dup2() failed and errno is set
		if (errno == EBADF)
			cout << "Newfd is out of range." << endl;
		if (errno == EINTR)
			cout << "Interrupted by a signal." << endl;
		if (errno == EMFILE)
			cout << "Process already has the max. number of fds open." << endl;
		if (errno == EBADF)
			cout << "Fd is not a valid fd." << endl;
		if (errno == EINTR)
			cout << "Interrupted by a signal." << endl;
		if (errno == EIO)
			cout << "I/O error occured." << endl;
			
		cout << "Dup2() failed." << endl;
		return false;
	}
	return true;
}
