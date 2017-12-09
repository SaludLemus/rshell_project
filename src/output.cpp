#include "output.h"
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
Output::Output(){output_file = 0; }

Output::Output(Base* ln, Base* rn){output_file = rn->getCommand();
}

Output::~Output(){output_file = 0;}

bool Output::execute(){
	bool succeed = true;

	output_file = rightNode->getCommand();
	
	if (!leftNode || !rightNode) {
		return false;
	}
	
	int save_1 = dup(1); // save [1]
	
	//check dup()
	if (!check_dup(save_1)) {
		return false;
	}
		
	int save_file_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR); // set fd for file
	
	if (save_file_fd == -1) {// open() failed
		close(save_1);
		return false;
	}
	
	dup2(save_file_fd, 1); // change fd for file to [1]
	
	close(save_file_fd); // close fd for file
	
	if (leftNode->getCommand() == 0) { // if left side is a connector ;, &&, ||, etc.
		if (!leftNode->execute()) {
			succeed = false;
		}

		dup2(save_1, 1);
		close(save_1);
		return succeed;
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

	if (!execute(exec_cmds)) { // execute
		succeed = false;
	}

	int index = 0;
	while (exec_cmds[index] != 0) { // set all to 0
		exec_cmds[index] = 0;
		++index;
	}
	delete[] exec_cmds; // dealloc mem.
	
	dup2(save_1, 1); // change what [1] was back to [1]
	
	close(save_1); // close fd that was opened
	
	return succeed;
}

void Output::display(){
    leftNode->display();
    std::cout << "|" << std::endl;
    rightNode->display();
}

bool Output::check_dup(int save_1) {
	if (save_1 == -1) { // dup() failed and errno is set
		return false;
	}
	return true;
}

bool Output::execute(char** commandArray){
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
