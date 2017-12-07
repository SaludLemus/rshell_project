#include "append.h"
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
Append::Append(){file_name = 0; }

Append::Append(Base* ln, Base* rn){file_name = rn->getCommand();}

Append::~Append(){file_name = 0;}

bool Append::execute(){
	if (!file_name) {
		file_name = rightNode->getCommand();
	}
	
	int save_1 = dup(1); // save [1]
	
	//check dup()
	if (!check_dup(save_1)) {
		return false;
	}
		
	int save_file_fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR); // set fd for file
	
	if (save_file_fd == -1) {// open() failed
		close(save_1);
		return false;
	}
	
	dup2(save_file_fd, 1); // change fd for file to [1]
	
	close(save_file_fd); // close fd for file
	
	if (!leftNode->execute()) {
		dup2(save_1, 1);
		close(save_1);
		return false;
	}
	// FILE IS ALREADY IN APPEND MODE
	
	// LOOP THROUGH IF THERE ARE MORE FILES
	char* add_cmd[3] = {0};
	add_cmd[0] = leftNode->getCommand();
	add_cmd[1] = rightNode->currentCommand();
	add_cmd[2] = 0;
	
	while(add_cmd[1] != NULL || add_cmd[1] != 0) {
		execute(add_cmd);
		add_cmd[1] = rightNode->currentCommand();
	}
	
	
	dup2(save_1, 1); // change what [1] was back to [1]
	
	close(save_1); // close fd that was opened
	
	return true;
}

void Append::display(){
    leftNode->display();
    std::cout << ">>" << std::endl;
    rightNode->display();
}

bool Append::check_dup(int save_1) {
	if (save_1 == -1) { // dup() failed and errno is set
		if (errno == EBADF)
			cout << "New fd is out of the allowed range." << endl;
		
		cout << "Dup() failed.)" << endl;
		return false;
	}
	return true;
}

bool Append::check_close() {
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


bool Append::change_output() {
	// open(const char* FILE_NAME, INT FLAGS)
	// file will be write only and will be created if DNE and append info. to the end
	if (open(file_name, O_WRONLY | O_CREAT | O_APPEND)) { // open() failed and errno is set
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

bool Append::restore_save1(int save_1) {
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

bool Append::execute(char** commandArray){
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
