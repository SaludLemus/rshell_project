#include "output.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <iostream>
using namespace std;
Output::Output(){output_file = 0; }

Output::Output(Base* ln, Base* rn){output_file = rn->getCommand();
}

Output::~Output(){output_file = 0;}

bool Output::execute(){
	output_file = rightNode->getCommand();
	//cout << "FILENAME: " << rightNode->getCommand() << endl;
	//cout << "LEFT SIDE: " << leftNode->getCommand() << endl;
	
	if (!leftNode || !rightNode)
		return false;
	
	//int save_1 = dup(1); // save [1]
	//int save_file_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC); // set fd for file
	
	//if (save_file_fd == -1)
		//return false;
	
	//dup2(save_file_fd, 1);
	//close(save_file_fd);
	//leftNode->execute();
	//dup2(save_1, 1);
	//close(save_1);
	
	int save_1 = dup(1); // save [1]
	
	//check dup()
	if (!check_dup(save_1))
		return false;
		
	 //check close() and close [1]
	if (!check_close())
		return false;
		
	// set fd for file to [1] via open()
	if (!change_output())
		return false;
		
	// check execute()
	if (!leftNode->execute()) // child failed
		return false;
		
	// restore save_1 and check
	if (!restore_save1(save_1))
		return false;
			
	return true;
}

void Output::display(){
    leftNode->display();
    std::cout << "|" << std::endl;
    rightNode->display();
}

bool Output::check_dup(int save_1) {
	if (save_1 == -1) { // dup() failed and errno is set
		if (errno == EBADF)
			cout << "New fd is out of the allowed range." << endl;
		
		cout << "Dup() failed.)" << endl;
		return false;
	}
	return true;
}

bool Output::check_close() {
	if (close(1) == -1) { // close() failed and errno is set
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


bool Output::change_output() {
	// open(const char* FILE_NAME, INT FLAGS)
	// file will be write only and will be created if DNE and truncate to zero bytes
	if (open(output_file, O_WRONLY | O_CREAT | O_TRUNC) == -1) { // open() failed and errno is set
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

bool Output::restore_save1(int save_1) {
	if (dup2(save_1, 1) == -1 || close(save_1) == -1) { // dup2() failed and errno is set
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
