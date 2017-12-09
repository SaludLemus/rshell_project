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
#include <vector>
using namespace std;

Input::Input(){file_name = 0;}

Input::Input(Base* ln, Base* rn){file_name = rn->getCommand();}

Input::~Input(){file_name = 0;}

bool Input::execute(){
	bool succeed = true;
	if (!leftNode || !rightNode) {
		return false;
	}

	int first_file = open(rightNode->getCommand(), O_RDONLY, S_IRUSR | S_IWUSR);
	
	if (first_file == -1) {
		perror("File does not exist.");
		return false;
	}

	vector<char*> total_cmds; // will contain char* of left and right sides' files

	// get left side's file
	char* cur_cmd = leftNode->currentCommand();
	while (cur_cmd != NULL) {
		total_cmds.push_back(cur_cmd);
		cur_cmd = leftNode->currentCommand();
	}

	// get right side's file
	cur_cmd = rightNode->currentCommand();
	while (cur_cmd != NULL) {
		total_cmds.push_back(cur_cmd);
		cur_cmd = rightNode->currentCommand();
	}
	// create char** with size of cmd plus vector's size and add
	int size_cmds = total_cmds.size() + 2;

	char** exec_cmds = new char*[sizeof(char*) * size_cmds];
	exec_cmds[0] = leftNode->getCommand(); // set [0] to command

	for (unsigned int i = 0; i < total_cmds.size(); ++i) { // copy over char* to char**
		exec_cmds[i + 1] = total_cmds.at(i);
	}
	exec_cmds[size_cmds - 1] = 0; // null term.

	// change [0] to file of first file on the right side
	int save_0 = dup(0);

	if (!check_dup(save_0)) { // dup() failed
		close(first_file);

		int index = 0;
		while (exec_cmds[index] != 0) { // set all to 0
			exec_cmds[index] = 0;
			++index;
		}
		delete[] exec_cmds; // dealloc mem.
		return false;
	}

	dup2(first_file, 0);
	close(first_file);

	if (!execute(exec_cmds)) { // for && and ||
		succeed = false;
	}

	int index = 0;
	while (exec_cmds[index] != 0) { // set all to 0
		exec_cmds[index] = 0;
		++index;
	}
	delete[] exec_cmds; // dealloc mem.

	dup2(save_0, 0);
	close(save_0);

	return succeed;
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
