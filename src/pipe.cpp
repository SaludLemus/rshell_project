#include "pipe.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <iostream>
using namespace std;

Pipe::Pipe(){ }

Pipe::Pipe(Base* ln, Base* rn){ }

Pipe::~Pipe(){ }

// assumes class has a left and right child
bool Pipe::execute() {
	if (leftNode || rightNode)
		return false;
		
	 // both childs exist
	int save_0 = dup(0); // save [0] and [1]
	int save_1 = dup(1);
	int fds[2]; // for pipe()
	
	// check dup()
	if (!check_dup(save_0, save_1))
		return false;
		
		// close 0 and 1
	if (!check_close())
		return false;
		
	// pipe() and check
	if (!check_pipe(fds))
		return false;
		
	// execute left child and check
	if (!leftNode->execute()) // left child failed
		return false;
		
	// restore save_1 via dup2() and check ===== dup2(int oldfd, int newfd) // copies newfds will be a copy of oldfd
	if (!restore_save1(save_1))
		return false;
		
	// execute right_child
	if (!rightNode->execute()) // right child failed
		return false;
		
	// restore save_0 via dup2() and check
	if (!restore_save0(save_0))
		return false;
		
	return true;
}

void Pipe::display(){
    leftNode->display();
    std::cout << "|" << std::endl;
    rightNode->display();
}

bool Pipe::check_dup(int save_0, int save_1) {
	if (save_0 == -1 || save_1 == -1) { // dup() failed and errno is set
		if (errno == EBADF)
			cout << "New fd is out of the allowed range." << endl;
		
		cout << "Dup() failed.)" << endl;
		return false;
	}
	return true;
}


bool Pipe::check_close() {
	if (close(0) == -1 || close(1) == -1) { // close() failed and errno is set
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

bool Pipe::check_pipe(int fds[2]) {
	if (pipe(fds) == -1) { // pipe() failed and errno is set
		if (errno == EFAULT)
			cout << "Pipefd is not valid." << endl;
		if (errno == EMFILE)
			cout << "Too many fds are in use by the process." << endl;
		if (errno == ENFILE)
			cout << "System limit on number of files allowed." << endl;
			
		cout << "Pipe() failed."  << endl;
		return false;
	}
	return true;
}


bool Pipe::restore_save1(int save_1) {
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

bool Pipe::restore_save0(int save_0) {
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
