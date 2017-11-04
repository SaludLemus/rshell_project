#include "defaultcommand.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <string>
#include <errno.h>
#include <stdio.h>
#include <cstdlib>
using namespace std;

DefaultCommand::DefaultCommand() : Connector(), exec_command(0) {}

DefaultCommand::DefaultCommand(CommandLine* new_cmd) : Connector(), exec_command(new_cmd) {}

void DefaultCommand::execute() {
	if (exec_command == 0)
		return;
	
	if (checkExistence()) {
		pid_t child_pid; // for fork()
		int child_status; // for waitpid()
		char** argv = exec_command->getCommand();
		
		checkExit(argv[0]); // exit prog if exit exists
		cmdSuccess = true;
		child_pid = fork(); // create child process fork() returns an integer (0 == child)
		
		if (child_pid == 0) { // child will run cmd
		
			if (execvp(argv[0], argv) < 0) {// returns a negative value if failed to execute
				cmdSuccess = false;
				perror("ERROR: Unknown command"); // error
				exit(EXIT_FAILURE);
			}
		}
		
		else if (child_pid == -1) {// fork failed
			cmdSuccess = false;
			perror("ERROR: Unable to fork a child process"); // error message
			exit(EXIT_FAILURE);
		}
		else { // parent has to wait for the child to be done
			pid_t check_pid = waitpid(child_pid, &child_status, 0);
			do {
				
				if (errno == EINTR) {// will set errno to EINTR if waitpid returns -1
					cmdSuccess = false;
					perror("ERROR: Function was interrupted");
					exit(EXIT_FAILURE);
				}
				else if (check_pid == 0)
					cmdSuccess = false;
				else if (WIFEXITED(child_status)) {
					if (WEXITSTATUS(child_status) == EXIT_FAILURE) {
					cmdSuccess = false;
					}
				}
					
			} while(check_pid != child_pid);
		}
		//if (argv)
			//delete[] argv;
	}
	
	return;
}

bool DefaultCommand::checkExistence() {
	if (exec_command) return true;
	return false;
}

bool DefaultCommand::checkStatus() {
	return cmdSuccess;
}

CommandConnector DefaultCommand::getConnector() {
	if (checkExistence()) 
		return exec_command->getConnector();
	return exitCC;
}
    
char** DefaultCommand::getCMD() {
	return exec_command->getCommand();	
}

void DefaultCommand::exitProg() {
	exit(0);
	return;
}

void DefaultCommand::checkExit(char* check_cmd) {
	string exit_str(check_cmd);
	
	if (exit_str == "exit")
		exitProg();
	return;
}
