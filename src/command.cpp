#include "command.h"
#include <iostream>
#include <errno.h>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;
Command::Command(){
    commandArray = new char*[1];
    commandArray[0] = NULL;
}

Command::Command(char** cmdArray){
    commandArray = cmdArray;
}

Command::~Command(){
    delete[] commandArray;
}

bool Command::execute(){
	if (commandArray== 0) // points to char* that is mem. loc. 0
		return false;
		
	pid_t child_pid; // for fork()
	int child_status; // for waitpid()
	
	//checkExit(commandArray[0]); // exit prog if exit exists
	child_pid = fork(); // create child process fork() returns an integer (0 == child)
		
	if (child_pid == 0) { // child will run cmd
		
		if (execvp(commandArray[0], commandArray) < 0) {// returns a negative value if failed to execute
			perror("ERROR: Unknown command"); // error
			//cout << "ERROR in child process returning to parent process" << endl;
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
	//cout << "returning true" << endl;
    return true;
}

void Command::display(){
    unsigned index = 0;
    while(commandArray[index] != NULL){
        std::cout << commandArray[index] << " ";
        index++;
    }
    std::cout << std::endl;
}
