#include "input.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <iostream>
using namespace std;

Input::Input(){file_name = 0;}

Input::Input(Base* ln, Base* rn){file_name = rn->getCommand();}

Input::~Input(){file_name = 0;}

bool Input::execute(){
	if (!leftNode || !rightNode) {
		return false;
	}

	if (leftNode->currentCommand() != NULL) { // files exist on the left side
		// set file_name to first file on the right side
		file_name = rightNode->getCommand();
	}
	else { // left side has no files
		// check right side if more files exist
		char* next_file = rightNode->currentCommand();

		if (next_file != NULL) { // more files exist, so ignore first file
			int first_file = open(rightNode->getCommand(), O_RDONLY, S_IRUSR | S_IWUSR);

			if (first_file == -1) { // file does not exist
				perror("File does not exist.");
				return false;
			}
			else {
				if (close(first_file) == -1) {
					perror("File does not exist.");
					return false;
				}
				file_name = next_file;
			}
		}
		else{ // only one file exists
			file_name = rightNode->getCommand();
		}
	}
		
	int save_0 = dup(0); // save [0]
	
	//check dup()
	if (!check_dup(save_0)) {
		return false;
	}

	int save_file_fd = open(file_name, O_RDONLY, S_IRUSR | S_IWUSR); // set fd for file
	
	if (save_file_fd == -1) {// open() failed
		perror("Error: File does not exist");

		if (file_name == rightNode->getCommand()) { // terminate if first file DNE
			close(save_0);
			return false;
		}
	}
	
	if (save_file_fd != -1) {
		dup2(save_file_fd, 0); // change fd for file to [0]

		close(save_file_fd); // close fd for file
	
		if (!leftNode->execute()) {
			dup2(save_0, 0);
			close(save_0);
			return false;
		}
	
		dup2(save_0, 0); // change what [0] was back to [0]
	
		close(save_0); // close
	}

	char* add_cmd[2] = {0}; // execute remaining files, if any
	add_cmd[0] = leftNode->getCommand();
//	add_cmd[1] = rightNode->currentCommand();
	add_cmd[1] = 0;
	char* cur_cmd = rightNode->currentCommand();

	while(cur_cmd != NULL) {
		save_file_fd = open(cur_cmd, O_RDONLY, S_IRUSR | S_IWUSR); // open file

		if (save_file_fd == -1) { // open failed
			perror("File does not exist.");
		}
		else {
			save_0 = dup(0); // set fds

			if(!check_dup(save_0))
				return false;

			dup2(save_file_fd, 0);
			close(save_file_fd);

			execute(add_cmd); // execute

			dup2(save_0, 0); // restore
			close(save_0);
		}

		cur_cmd = rightNode->currentCommand(); // get next command
	}

	return true;
}

void Input::display(){
    leftNode->display();
    std::cout << "<" << std::endl;
    rightNode->display();
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

bool Input::execute(char** commandArray){
	if (commandArray== 0) // points to char* that is mem. loc. 0
		return false;

	pid_t child_pid; // for fork()
	int child_status; // for waitpid()

	child_pid = fork(); // create child process fork() returns an integer (0 == child)

	if (child_pid == 0) { // child will run cmd

		if (execvp(commandArray[0], commandArray) < 0) {// returns a negative value if failed to execute
			perror("ERROR: Unknown command"); // error
			//cout << "ERROR in child process returning to parent process" << endl;
			//cout << "ERROR" << endl;
			exit(EXIT_FAILURE);
		}
	}

	else if (child_pid == -1) {// fork failed
		perror("ERROR: Unable to fork a child process"); // error message
		exit(EXIT_FAILURE);
	}
	else { // parent has to wait for the child to be done
		pid_t check_pid;
		do {
			check_pid = waitpid(child_pid, &child_status, 0);
			if (errno == EINTR) {// will set errno to EINTR if waitpid returns -1
				perror("ERROR: Function was interrupted");
				exit(EXIT_FAILURE);
				return false;
			}
			else if (WIFEXITED(child_status) && WEXITSTATUS(child_status) == EXIT_FAILURE) { // child process did not execute
				//cout << "returning false" << endl;
				return false;
			}

		} while(check_pid != child_pid);
	}

    return true;
}
